#pragma once
#ifndef CURL_UTILITIES_H
#define CURL_UTILITIES_H
#include "webinclude.hpp"
using cyh::data::text;

namespace cyh::web {

	class CurlUtilities {
	public:
		static size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s)
		{
			size_t newLength = size * nmemb;
			try
			{
				s->append((char*)contents, newLength);
			}
			catch (std::bad_alloc& e)
			{
				//handle memory problem
				return 0;
			}
			return newLength;
		}

		static size_t writer(char* data, size_t size, size_t nmemb, std::string* writerData)
		{
			if (writerData == NULL) { return 0; }
			writerData->append(data, size * nmemb);
			return size * nmemb;
		}
		static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
		{
			size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
			return written;
		}
	};
}


#endif