#pragma once
#ifndef TEXT_H
#define TEXT_H
#include <tchar.h>
#include "../thirdpartylib.hpp"
#include "../struct/iterator.hpp"
using std::vector;
using std::string;
using std::wstring;
using cyh::Struct::Iterator;
namespace cyh::data {
	class Convert;
	class text {
	private:
#pragma region friend_members
		friend class Convert;
		friend const char*& operator+(const char* cchptr, text txt) {
			cchptr = cchptr + txt;
			return cchptr;
		};
		friend const wchar_t*& operator+(const wchar_t* cchptr, text txt) {
			cchptr = cchptr + txt;
			return cchptr;
		};
		friend std::string& operator+=(std::string& str, text txt) {
			str += txt.ToStr();
			return str;
		};
		friend std::wstring& operator+(std::wstring& wstr, text txt) {
			wstr += txt.m_wstr;
			return wstr;
		};
		friend std::string operator+(string str, text txt) {
			return str + txt.ToStr();
		};
		friend std::wstring operator+(wstring str, text txt) {
			return str + txt.m_wstr;
		};
		friend std::ofstream& operator<< (std::ofstream& os, text& txt) {
			os << txt.ToStr();
			return os;
		}
		friend std::vector<text>& operator << (vector<text>& txts, text txt) {
			txts.push_back(txt);
			return txts;
		}
#pragma endregion
		Convert* conv = nullptr;
		void _clear();
		void _set(unsigned n);
		void _set(int n);
		void _set(double n);
		void _set(char c);
		void _set(wchar_t c);
		void _set(string str);
		void _set(std::wstring str);
		void _set(text str);

		void set_by_ref(string& str);
		void set_by_ref(std::wstring& str);
		void set_by_ref(text& str);
		void set_by_ref(const string& str);
		void set_by_ref(const std::wstring& str);
		void set_by_ref(const text& str);

		void _add(const unsigned c);
		void _add(const int c);
		void _add(const double c);
		void _add(const char c);
		void _add(const wchar_t c);
		void _add(string s);
		void _add(std::wstring s);
		void _add(text s);

		void add_by_ref(string& s);
		void add_by_ref(std::wstring& s);
		void add_by_ref(text& s);
		void add_by_ref(const string& s);
		void add_by_ref(const std::wstring& s);
		void add_by_ref(const text& s);

		bool _inRange(size_t index);
		bool _rangeValid(size_t index_start, size_t index_end);
		size_t _findIndexStartFrom(size_t startIndex, string str);
		size_t _findIndexEndFrom(size_t startIndex, string str);
		size_t find_index_start_from(size_t startIndex, std::wstring& str);
		size_t find_index_end_from(size_t startIndex, std::wstring& str);
		size_t find_index_start_from(size_t startIndex, text& str);
		size_t find_index_end_from(size_t startIndex, text& str);
		text _splitProcess(size_t index_start, text sStart, text sEnd, size_t* iReserve);
		text _subStr(size_t iStart, size_t iEnd);
		std::wstring m_wstr;
	public:	
		size_t Length;
#pragma region construct_and_destroy
		text() :m_wstr(L""), Length(0) {}
		text(text txt, int n) { FillWith(txt, n); }
		text(unsigned n) { _set((double)n); }
		text(int n) { _set((double)n); }
		text(char c) { _set(c); }
		text(wchar_t c) { _set(c); }
		text(double n) { _set(n); }
		text(const char* cptr) { _set((string)cptr); }
		text(const wchar_t* cptr) { _set((wstring)cptr); }
		text(string s) { _set(s); }
		text(std::wstring s) { _set(s); }
		text(vector<text> v);
		text(vector<text>& v);
		text(const text& t) { _set(t.m_wstr); }
		~text() { _clear(); }
#pragma endregion
#pragma region operator_overload
		operator std::string();
		operator std::wstring();
		operator const char* ();
		operator const wchar_t* ();
		operator LPWSTR ();
		double ToDouble();
		std::string ToStr();
		std::wstring ToWStr();
		wchar_t& operator[](size_t i);

		text operator + (const unsigned& n);
		text operator + (const int& n);
		text operator + (const double& n);	
		text operator + (const char& c);
		text operator + (const wchar_t& c);
		text operator + (const char* chptr);
		text operator + (const wchar_t* chptr);
		text operator + (const string& str);
		text operator + (const wstring& str);
		text operator + (const text& t);
		text operator + (const vector<text>& v);

		text& operator = (const unsigned& n);
		text& operator = (const int& n);
		text& operator = (const double& n);
		text& operator = (const char& c);
		text& operator = (const wchar_t& c);
		text& operator = (const char* chptr);
		text& operator = (const wchar_t* chptr);
		text& operator = (const string& str);
		text& operator = (const wstring& str);
		text& operator = (const text& str);
		text& operator = (const vector<text>& v);

		text& operator += (const unsigned& n);
		text& operator += (const int& n);
		text& operator += (const double& n);
		text& operator += (const char& c);
		text& operator += (const wchar_t& c);
		text& operator += (const char* chptr);
		text& operator += (const wchar_t* chptr);
		text& operator += (const string& str);
		text& operator += (const wstring& str);
		text& operator += (const text& str);
		text& operator += (const vector<text>& v);

		bool operator == (const unsigned& n);
		bool operator != (const unsigned& n);
		bool operator == (const int& n);
		bool operator != (const int& n);
		bool operator == (const double& n);
		bool operator != (const double& n);
		bool operator == (const char& c);
		bool operator != (const char& c);
		bool operator == (const wchar_t& c);
		bool operator != (const wchar_t& c);
		bool operator == (const char* chptr);
		bool operator != (const char* chptr);
		bool operator == (const wchar_t* chptr);
		bool operator != (const wchar_t* chptr);
		bool operator == (const string& str);
		bool operator != (const string& str);
		bool operator == (const text& t);
		bool operator != (const text& t);
#pragma endregion
#pragma region wchar_iterator
		wchar_t* first = nullptr;
		wchar_t* last = nullptr;
		Iterator<wchar_t> begin()
		{
			return Iterator(first);
		}
		Iterator<wchar_t> end()
		{
			return Iterator(last);
		}
#pragma endregion
		bool Contain(string t);
		bool Contain(wstring& t);
		bool Contain(text t);
		bool IsBetween(text t);
		size_t CountOf(text t);
		size_t EndIndexOf(text t);
		size_t EndIndexOf(size_t iStart, text t);
		size_t FirstIndexOf(text t);
		size_t LastIndexOf(text t);

		text SubString(size_t index_start);
		text SubString(size_t index_start, size_t index_end);
		text Between(size_t index_start, size_t index_end);
		text Between(text strStart, text strEnd);
		text Between(size_t index_start, text strStart, text strEnd);
		vector<text> Betweens(size_t index_start, text strStart, text strEnd);
		vector<text> Betweens(text strStart, text strEnd);
		vector<text> Splits(text _text);
		vector<text> GetContentEnvloped(text _envStart, text _envEnd);

		bool IsEnveloped(text _envStart, text _envEnd);
		bool StartWith(text txt);
		bool EndWith(text txt);
		void FillWith(text txt, int times);
		void Replace(text target, text result);		
		void ReplaceAll(text target, text result);
		void AddWrapping(text t);
		void Trim();
		void RemoveAll(char target);
		void RemoveAll(wchar_t target);
	};
}
#endif // !TEXT_H


