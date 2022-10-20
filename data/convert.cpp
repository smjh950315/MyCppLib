#include "tuples.hpp"
#include "convert.hpp"
using Convert = cyh::Convert;


std::string Convert::ToNarrowStr(std::wstring_view str) {
	auto length = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.length(), nullptr, 0, nullptr, nullptr);
	std::string narrowStr{};
	narrowStr.resize(length);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.length(), (LPSTR)narrowStr.c_str(), length, nullptr, nullptr);
	return narrowStr;
}
std::wstring Convert::ToWideStr(std::string_view str) {
	auto length = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.length(), nullptr, 0);
	std::wstring wideStr{};
	wideStr.resize(length);
	MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.length(), (LPWSTR)wideStr.c_str(), length);
	return wideStr;
}


