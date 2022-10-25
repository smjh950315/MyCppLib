#pragma once
#ifndef CURL_CLIENT_H
#define CURL_CLIENT_H
#include "curlutilities.hpp"
#include "modify.hpp"
#include "webobj/webform.hpp"
#include "../time/time.hpp"
#include <iostream>
using cyh::data::text;
using cyh::Time::Timer;
using cyh::web::WebForm;
using cyh::web::Modify;
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
		void SetUrl(text _url);
		void HttpGet();
		void HttpGet(text& buffer);
		void HttpPost(text content_to_post);
		void HttpPost(text content_to_post, text& buffer);
		
		//static method
		static void HttpGet(text url, text& buffer, Timer& t);
		static void HttpPost(text url, text& content_to_post, text& buffer, Timer& t);
	};


}


#endif // !CURL_CLIENT_H
