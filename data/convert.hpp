#pragma once
#ifndef CONVERT_H
#define CONVERT_H
#include "../thirdpartylib.hpp"
#include <opencv2/opencv.hpp>
#include "text.hpp"
#include "datetime.hpp"

using cyh::data::text;
using cyh::data::DateTime;
using cv::Mat;
namespace cyh {
	namespace data {
		static const char brStart = '(';
		static const char brEnd = ')';
		static const char sqbrStart = '[';
		static const char sqbrEnd = ']';
		static const char clbrStart = '{';
		static const char clbrEnd = '}';
		static const char qMark = '\"';
	}
	class Convert {
	private:
	public:
		Convert() {}
		static std::string ToNarrowStr(std::wstring_view str);
		static std::wstring ToWideStr(std::string_view str);

	};

}

#endif