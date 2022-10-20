#pragma once
#ifndef CURL_CLIENT_H
#define CURL_CLIENT_H
#include "curlutilities.hpp"
#include "webobj/webform.hpp"
#include "../time/time.hpp"
#include <iostream>
using cyh::data::text;
using cyh::Time::Timer;
using cyh::web::WebForm;
//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

namespace cyh::web {

	class CurlClient :public CurlUtilities {
	private:
		void _init();
		void _write(text& buffer);
		void _http_get(text& buffer, bool write_buffer);
		void _http_post(text& post, text& buffer, bool write_buffer);
		void _http_post(WebForm& _form, text& buffer, bool write_buffer);
		void _http_fin();
		void _use_cookie();
		text nobuf = "";
	public:		
		long MaxRedirection = 3;
		bool UseHttps = false;
		bool UseVerbose = false;
		bool UseCookie = false;
		CURL* curl = nullptr;
		curl_mime* form = nullptr;
		curl_mimepart* field = nullptr;
		struct curl_slist* sList = nullptr;
		CURLcode res = {};
		text Url = "";
		text ClientType = "curl/7.38.0";	
		text Cookie="";
		text CookiePath = "";

		CurlClient() {}
		CurlClient(text url) :Url(url) {}

		void HttpGet();
		void HttpGet(text& buffer);
		void HttpPost(text content_to_post);
		void HttpPost(text content_to_post, text& buffer);
		//void HttpPost(WebForm& _form);
		static void HttpGet(text url, text& buffer, Timer& t) {
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
		static void HttpPost(text url, text content_to_post, text& buffer, Timer& t) {
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
	};


}


#endif // !CURL_CLIENT_H
