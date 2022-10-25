#include "curlclient.hpp"
using cyh::web::CurlClient;

void CurlClient::_init() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
}
void CurlClient::_write(text& buffer) {
	std::string temp = "";
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &temp);
	res = curl_easy_perform(curl);
	buffer = temp;
}
void CurlClient::_http_get(text& buffer, bool write_buffer) {
	_init();
	if (curl) {
		if (UseCookie) {
			_use_cookie();
		}
		if (UseHttps) {
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		}
		curl_easy_setopt(curl, CURLOPT_URL, (const char*)Url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, MaxRedirection);
		if (UseVerbose) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}
		if (write_buffer) {
			_write(buffer);
		}
		else {
			res = curl_easy_perform(curl);
		}
		_http_fin();
	}
	curl_global_cleanup();
}
void CurlClient::_http_post(text& post, text& buffer, bool write_buffer) {
	_init();
	if (curl) {
		sList = NULL;
		sList = curl_slist_append(sList, "Content-Type: application/json");
		if (UseCookie) {
			_use_cookie();
		}
		if (UseHttps) {
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		}
		curl_easy_setopt(curl, CURLOPT_URL, (const char*)Url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, sList);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (const char*)post);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, (const char*)ClientType);
		if (UseVerbose) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}
		if (write_buffer) {
			_write(buffer);
		}
		else {
			res = curl_easy_perform(curl);
		}
		_http_fin();
	}
	curl_global_cleanup();
}
void CurlClient::_http_post(WebForm& _form, text& buffer, bool write_buffer) {
	_init();
	if (curl) {
		if (UseCookie) {
			_use_cookie();
		}
		struct curl_httppost* formpost = NULL;
		struct curl_httppost* lastptr = NULL;
		struct curl_slist* headerlist = NULL;
		static const char buf[] = "Expect:";

		for (auto data : _form.Data) {
			curl_formadd(&formpost,
				&lastptr,
				CURLFORM_COPYNAME, (const char*)data.Key,
				CURLFORM_COPYCONTENTS, (const char*)data.Value,
				CURLFORM_END);
		}
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "submit",
			CURLFORM_COPYCONTENTS, "send",
			CURLFORM_END);

		if (UseVerbose) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}
		if (write_buffer) {
			_write(buffer);
		}
		else {
			res = curl_easy_perform(curl);
		}
		_http_fin();
	}
	curl_global_cleanup();
}
void CurlClient::_http_fin() {
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}
	curl_easy_cleanup(curl);
	if (UseCookie) {
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, (const char*)CookiePath);
	}
}
void CurlClient::_use_cookie() {
	if (Cookie.Length != 0) {
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, (const char*)CookiePath); // activate cookie engine
	}
	else {
		curl_easy_setopt(curl, CURLOPT_COOKIE, (const char*)Cookie);
	}	
}

void CurlClient::SetUrl(text _url) {
	Url = _url;
}
void CurlClient::HttpGet() {
	_http_get(nobuf, 0);
}
void CurlClient::HttpGet(text& _buffer) {
	_http_get(_buffer, 1);
}
void CurlClient::HttpPost(text content_to_post) {
	_http_post(content_to_post, nobuf, 0);
}
void CurlClient::HttpPost(text content_to_post, text& _buffer) {
	_http_post(content_to_post, _buffer, 1);
}

//static method
void CurlClient::HttpGet(text url, text& buffer, Timer& t) {
	CURL* curl;
	struct curl_slist* sList = nullptr;
	CURLcode res = {};
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		sList = NULL;
		sList = curl_slist_append(sList, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_URL, (const char*)url);
		std::string temp = "";
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &temp);
		t.Start();
		res = curl_easy_perform(curl);
		t.End();
		buffer = temp;
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
void CurlClient::HttpPost(text url, text& content_to_post, text& buffer, Timer& t) {
	CURL* curl;
	struct curl_slist* sList = nullptr;
	CURLcode res = {};
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		sList = NULL;
		sList = curl_slist_append(sList, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_URL, (const char*)url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, sList);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		Modify::PureJsonString(content_to_post);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (const char*)content_to_post);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.38.0");
		std::string temp = "";
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &temp);
		t.Start();
		res = curl_easy_perform(curl);
		t.End();
		buffer = temp;
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

