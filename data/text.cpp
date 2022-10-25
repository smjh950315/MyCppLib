#include "convert.hpp"
#include "text.hpp"
using Convert = cyh::Convert;
using cyh::data::text;

void text::_clear() {
	this->m_wstr.clear();
	Length = m_wstr.length();
}
void text::_set(unsigned n) {
	_set(std::to_wstring(n));
}
void text::_set(int n) {
	_set(std::to_wstring(n));
}
void text::_set(double n) {
	_set(std::to_wstring(n));
}
void text::_set(char c) {
	string s = "" + c;
	_set(cyh::Convert::ToWideStr(s));
}
void text::_set(wchar_t c) {
	m_wstr += c;
	_set(m_wstr);
}
void text::_set(string str) {
	_set(cyh::Convert::ToWideStr(str));
}
void text::_set(std::wstring str) {
	this->m_wstr = str;
	Length = m_wstr.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::_set(text t) {
	_set(t.m_wstr);
}

void text::set_by_ref(string& str) {
	_set(cyh::Convert::ToWideStr(str));
}
void text::set_by_ref(std::wstring& str) {
	this->m_wstr = str;
	Length = m_wstr.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::set_by_ref(text& t) {
	set_by_ref(t.m_wstr);
}
void text::set_by_ref(const string& str) {
	_set(cyh::Convert::ToWideStr(str));
}
void text::set_by_ref(const std::wstring& str) {
	this->m_wstr = str;
	Length = m_wstr.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::set_by_ref(const text& t) {
	set_by_ref(t.m_wstr);
}

void text::_add(const unsigned n) {
	_add((double)n);
}
void text::_add(const int n) {
	_add((double)n);
}
void text::_add(const double n) {
	_add(std::to_wstring(n));
}
void text::_add(const char c) {
	string str = "" + (char)c;
	_add(cyh::Convert::ToWideStr(str));
}
void text::_add(const wchar_t c) {
	const wchar_t wcptr[] = {c,'\0'};
	_add((wstring)wcptr);
}
void text::_add(string str) {
	_add(cyh::Convert::ToWideStr(str));
}
void text::_add(std::wstring str) {
	this->m_wstr += str;
	Length += str.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::_add(text t) {
	add_by_ref(t.m_wstr);
}

void text::add_by_ref(string& str) {
	_add(cyh::Convert::ToWideStr(str));
}
void text::add_by_ref(std::wstring& str) {
	this->m_wstr += str;
	Length += str.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::add_by_ref(text& t) {
	_add(t.m_wstr);
}
void text::add_by_ref(const string& str) {
	_add(cyh::Convert::ToWideStr(str));
}
void text::add_by_ref(const std::wstring& str) {
	this->m_wstr += str;
	Length += str.length();
	first = &(m_wstr[0]);
	last = &(m_wstr[Length]);
}
void text::add_by_ref(const text& t) {
	_add(t.m_wstr);
}

bool text::_inRange(size_t i) {
	if (i < 0) { return false; }
	if (i + 1 > Length) { return false; }
	return true;
}
bool text::_rangeValid(size_t iStart, size_t iEnd) {
	if (iEnd > Length - 1) { return false; }
	if (iStart < 0) { return false; }
	if (iEnd < iStart) { return false; }
	return true;
}
size_t text::_findIndexStartFrom(size_t startIndex, string s) {
	return m_wstr.find(cyh::Convert::ToWideStr(s), startIndex);
}
size_t text::_findIndexEndFrom(size_t startIndex, string s) {
	size_t iStart = m_wstr.find(cyh::Convert::ToWideStr(s), startIndex);
	if (iStart == string::npos) {
		return string::npos;
	}
	return iStart + s.length() - 1;
}

size_t text::find_index_start_from(size_t startIndex, std::wstring& s) {
	return m_wstr.find(s, startIndex);
}
size_t text::find_index_end_from(size_t startIndex, std::wstring& s) {
	size_t iStart = m_wstr.find(s, startIndex);
	if (iStart == string::npos) {
		return string::npos;
	}
	return iStart + s.length() - 1;
}
size_t text::find_index_start_from(size_t startIndex, text& s) {
	return find_index_start_from(startIndex, s.m_wstr);
}
size_t text::find_index_end_from(size_t startIndex, text& s) {
	return find_index_end_from(startIndex, s.m_wstr);
}

text text::_splitProcess(size_t idStart, text sStart, text sEnd, size_t* iReserve) {
	if (idStart + 1 > Length) { return L""; }
	size_t minTotLen = idStart + sStart.Length + sEnd.Length;
	if (minTotLen >= Length) { return L""; }
	size_t iStart = _findIndexEndFrom(idStart, sStart);
	size_t iEnd = _findIndexStartFrom(iStart, sEnd);
	if (iStart == string::npos || iEnd == string::npos) {
		*iReserve = string::npos;
		return L"";
	}
	*iReserve = iEnd - 1;
	return _subStr(iStart + 1, iEnd - 1);
}
text text::_subStr(size_t iStart, size_t iEnd) {
	if (!_rangeValid(iStart, iEnd - 1)) { return L""; }
	return m_wstr.substr(iStart, iEnd - iStart);
}
text::text(vector<text> v) {
	_clear();
	for (auto& s : v) {
		add_by_ref(s);
	}
}
text::text(vector<text>& v) {
	_clear();
	for (auto& s : v) {
		add_by_ref(s);
	}
}

text::operator std::string() {
	return cyh::Convert::ToNarrowStr(m_wstr);
}
text::operator std::wstring() {
	return this->m_wstr;
}
double text::ToDouble() {
	return atoi(cyh::Convert::ToNarrowStr(m_wstr).c_str());
}
std::string text::ToStr() {
	return cyh::Convert::ToNarrowStr(m_wstr);
}
std::wstring text::ToWStr() {
	return m_wstr;
}
text::operator const char* () {
	string temp = cyh::Convert::ToNarrowStr(m_wstr);
	char* chptr = new char[Length + 1];
	for (int i = 0; i < Length; i++) {
		chptr[i] = temp[i];
	}
	chptr[Length] = '\0';
	return chptr;
}
text::operator const wchar_t* () {
	return (this->m_wstr).c_str();
}
text::operator LPWSTR () {
	return (wchar_t*)((this->m_wstr).c_str());
}
wchar_t& text::operator[](size_t i) {
	if (i < Length) {
		return m_wstr[i];
	}
	else {		
		return m_wstr[Length-1];
	}
}

text text::operator+(const unsigned& n) {
	return operator+(std::to_wstring(n));
}
text text::operator+(const int& n) {
	return operator+(std::to_wstring(n));
}
text text::operator+(const double& n) {
	return operator+(std::to_wstring(n));
}
text text::operator+(const char& c) {
	return operator+(std::to_wstring(c));
}
text text::operator+(const wchar_t& c) {
	return operator+(std::to_wstring(c));
}
text text::operator+(const char* c) {
	return operator+((string)c);
}
text text::operator+(const wchar_t* c) {
	return operator+((wstring)c);
}
text text::operator+(const string& str) {
	text _temp = m_wstr;
	_temp._add(str);
	return _temp;
}
text text::operator+(const wstring& str) {
	text _temp = m_wstr;
	_temp._add(str);
	return _temp;
}
text text::operator+(const text& str) {
	return operator+(str.m_wstr);
}
text text::operator+(const vector<text>& v) {
	text _temp = m_wstr;
	for (auto& s : v) {
		_temp._add(s.m_wstr);
	}
	return _temp;
}

text& text::operator=(const unsigned& n) {
	_set((int)n);
	return *this;
}
text& text::operator=(const int& n) {
	_set(n);
	return *this;
}
text& text::operator=(const double& n) {
	_set(n);
	return *this;
}
text& text::operator=(const char& c) {
	_set(c);
	return *this;
}
text& text::operator=(const wchar_t& c) {
	_set(c);
	return *this;
}
text& text::operator=(const char* chptr) {
	std::string str = chptr;
	set_by_ref(str);
	return *this;
}
text& text::operator=(const wchar_t* chptr) {
	std::wstring wstr = chptr;
	set_by_ref(wstr);
	return *this;
}
text& text::operator=(const string& str) {
	set_by_ref(str);
	return *this;
}
text& text::operator=(const wstring& str) {
	set_by_ref(str);
	return *this;
}
text& text::operator=(const text& str) {
	set_by_ref(str);
	return *this;
}
text& text::operator=(const vector<text>& v) {
	_clear();
	for (auto& s : v) {
		set_by_ref(s.m_wstr);
	}
	return *this;
}

text& text::operator+=(const unsigned& n) {
	_add((int)n);
	return *this;
}
text& text::operator+=(const int& n) {
	_add(n);
	return *this;
}
text& text::operator+=(const double& n) {
	_add(n);
	return *this;
}
text& text::operator+=(const char& c) {
	_add(c);
	return *this;
}
text& text::operator+=(const wchar_t& c) {
	_add(c);
	return *this;
}
text& text::operator+=(const char* chptr) {
	std::string str = chptr;
	_add(str);
	return *this;
}
text& text::operator+=(const wchar_t* chptr) {
	std::wstring wstr = chptr;
	_add(wstr);
	return *this;
}
text& text::operator+=(const string& str) {
	add_by_ref(str);
	return *this;
}
text& text::operator+=(const wstring& str) {
	add_by_ref(str);
	return *this;
}
text& text::operator+=(const text& str) {
	add_by_ref(str.m_wstr);
	return *this;
}
text& text::operator+=(const vector<text>& v) {
	for (auto& s : v) {
		add_by_ref(s.m_wstr);
	}
	return *this;
}

bool text::operator == (const unsigned& n) {
	return operator ==((double)n);
}
bool text::operator != (const unsigned& n) {
	return operator !=((double)n);
}
bool text::operator == (const int& n) {
	return operator ==((double)n);
}
bool text::operator != (const int& n) {
	return operator !=((double)n);
}
bool text::operator == (const double& n) {
	wstring wstr = cyh::Convert::ToWideStr(std::to_string(n));
	return m_wstr == wstr;
}
bool text::operator != (const double& n) {
	wstring wstr = cyh::Convert::ToWideStr(std::to_string(n));
	return m_wstr != wstr;
}
bool text::operator == (const char& c) {
	if (Length != 1) { return false; }
	string str = "" + c;
	return m_wstr == cyh::Convert::ToWideStr(str);
}
bool text::operator != (const char& c) {
	if (Length != 1) { return true; }
	string str = "" + c;
	return m_wstr != cyh::Convert::ToWideStr(str);
}
bool text::operator == (const wchar_t& c) {
	if (Length != 1) { return false; }
	string str = "" + c;
	return m_wstr[0] == c;
}
bool text::operator != (const wchar_t& c) {
	if (Length != 1) { return true; }
	string str = "" + c;
	return m_wstr[0] != c;
}
bool text::operator == (const char* chptr)
{
	return m_wstr == cyh::Convert::ToWideStr(chptr);
}
bool text::operator != (const char* chptr) {
	return m_wstr != cyh::Convert::ToWideStr(chptr);
}
bool text::operator == (const wchar_t* chptr)
{
	return m_wstr == chptr;
}
bool text::operator != (const wchar_t* chptr) {
	return m_wstr != chptr;
}
bool text::operator == (const string& str) {
	return m_wstr == cyh::Convert::ToWideStr(str);
}
bool text::operator != (const string& str) {
	return m_wstr != cyh::Convert::ToWideStr(str);
}
bool text::operator == (const text& text) {
	return m_wstr == text.m_wstr;
}
bool text::operator != (const text& text) {
	return m_wstr != text.m_wstr;
}

bool text::Contain(string t) {
	return Contain(cyh::Convert::ToWideStr(t));
}
bool text::Contain(wstring& t) {
	size_t i = m_wstr.find(t);
	if (i != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}
bool text::Contain(text t) {
	return Contain(t.m_wstr);
}
bool text::IsBetween(text t) {
	if (m_wstr.starts_with(t.m_wstr) && m_wstr.ends_with(t.m_wstr)) {
		return true;
	}
	return false;
}
size_t text::CountOf(text t) {
	int _count = 0;
	size_t iStart = 0;
	while (1) {
		size_t iFind = find_index_end_from(iStart, t);
		if (iFind == string::npos) { break; }
		_count++;
		iStart = iFind + 1;
	}
	return _count;
}
size_t text::EndIndexOf(text t) {
	return EndIndexOf(0, t);
}
size_t text::EndIndexOf(size_t iStart, text t) {
	return find_index_end_from(iStart, t);
}
size_t text::FirstIndexOf(text t) {
	return find_index_start_from(0, t);
}
size_t text::LastIndexOf(text t) {
	size_t iLastFound = string::npos;
	size_t countFind = 0;
	for (size_t iFind = 0; iFind < Length; iFind++) {
		iFind = find_index_start_from(iFind, t);
		if (iFind == std::string::npos) {			
			break;
		}
		else {
			iLastFound = iFind;
		}
	}
	return iLastFound;
}

text text::SubString(size_t iStart) {
	return _subStr(iStart, Length);
}
text text::SubString(size_t iStart, size_t iEnd) {
	return _subStr(iStart, iEnd);
}
text text::Between(size_t iStart, size_t iEnd) {
	return _subStr(iStart + 1, iEnd);
}
text text::Between(text sStart, text sEnd) {
	return Between(0, sStart, sEnd);
}
text text::Between(size_t idStart, text sStart, text sEnd) {
	if (idStart + 1 > Length) { return ""; }
	size_t minTotLen = idStart + sStart.Length + sEnd.Length;
	if (minTotLen >= Length) { return ""; }
	size_t iStart = find_index_end_from(idStart, sStart);
	size_t iEnd = find_index_start_from(iStart, sEnd);
	if (iStart == string::npos || iEnd == string::npos) {
		return L"";
	}
	return _subStr(iStart + 1, iEnd);
}

vector<text> text::Betweens(size_t idStart, text sStart, text sEnd) {
	vector<text> _v;
	size_t tempVal = 0;
	size_t iStart = idStart;
	while (1) {
		string _tmp = _splitProcess(iStart, sStart, sEnd, &tempVal);
		if (_tmp.length() < 1) { break; }
		_v.push_back(_tmp);
		iStart = tempVal;
	}
	return _v;
}
vector<text> text::Betweens(text sStart, text sEnd) {
	return Betweens(0, sStart, sEnd);
}
vector<text> text::Splits(text t) {
	vector<text> _v;
	size_t len = t.m_wstr.length();
	size_t iStart = 0;
	size_t iFind = 0;
	size_t iFindReserve = 0;
	size_t countFind = 0;
	while (1) {
		iFind = m_wstr.find(t.m_wstr, iStart);
		if (iFind == wstring::npos) { break; }
		countFind++;
		text s = m_wstr.substr(iStart, iFind - iStart);
		iStart = iFind + 1;
		if (s.Length > 0) {
			_v.push_back(s);
		}
		iFindReserve = iFind;
	}
	if (countFind == 0) {
		_v.push_back(m_wstr);
	}
	else if (iFindReserve < Length - 1) {
		_v.push_back(SubString(iFindReserve + 1, Length));
	}
	return _v;
}
vector<text> text::GetContentEnvloped(text _envStart, text _envEnd) {
	vector<text> brContent;
	text eS = _envStart;
	text eE = _envEnd;
	text temp = "";
	size_t countOfES = 0;
	size_t countOfEE = 0;
	for (size_t i = 0; i < Length; i++) {

		size_t fnd_s = find_index_start_from(i, eS);
		if (fnd_s == string::npos) { break; }
		else {
			i = fnd_s;
		}
		size_t fnd_e = find_index_start_from(i, eE);
		if (fnd_e == string::npos) { break; }
		else {
			while (1) {
				countOfES = _subStr(fnd_s + 1, fnd_e).CountOf(eS);
				countOfEE = _subStr(fnd_s + 1, fnd_e).CountOf(eE);
				if (countOfES == countOfEE) {
					temp = _subStr(fnd_s + 1, fnd_e);
					brContent.push_back(temp);
					temp = "";
					i = fnd_e + 1;
					break;
				}
				else {
					fnd_e = find_index_start_from(fnd_e + 1, eE);
				}
			}
		}
	}
	return brContent;
}

bool text::IsEnveloped(text _envStart, text _envEnd) {
	int countBrStart = 0;
	text eS = _envStart;
	text eE = _envEnd;
	for (auto& c : m_wstr) {
		if (countBrStart < 0) {
			break;
		}
		if (c == eE) {
			countBrStart--;
		}
		else if (c == eS) {
			countBrStart++;
		}
		else {}
	}
	if (countBrStart != 0)
	{
		return false;
	}
	else {
		return true;
	}
}
bool text::StartWith(text txt) {
	return find_index_start_from(0, txt) == 0;
}
bool text::EndWith(text txt) {
	return LastIndexOf(txt) + txt.Length == Length;
}
void text::FillWith(text txt, int times) {
	m_wstr = L"";
	for (int i = 0; i < times; i++) {
		m_wstr += txt.m_wstr;
	}
	Length = m_wstr.length();
}
void text::Replace(text target, text result) {
	size_t iStart = find_index_start_from(0, target);
	if (iStart == string::npos) {
		return;
	}
	m_wstr.replace(iStart, target.Length, result.m_wstr);
	Length = m_wstr.length();
}
void text::ReplaceAll(text target, text result) {
	size_t iStart = 0;
	while (iStart >= 0 && iStart < Length) {
		iStart = find_index_start_from(0, target);
		if (iStart == std::string::npos) {
			break;
		}
		if (iStart + target.Length >= Length) {
			break;
		}
		m_wstr.replace(iStart, target.Length, result.m_wstr);
		Length = m_wstr.length();
	}
	return;
}
void text::AddWrapping(text text) {
	m_wstr = text.m_wstr + m_wstr + text.m_wstr;
}
void text::Trim() {
	wstring temp = m_wstr;
	m_wstr.clear();
	wchar_t w_space = L' ';
	for (auto& wc : temp) {
		if (wc == w_space) { continue; }
		m_wstr += wc;
	}
	Length = m_wstr.length();
}
void text::RemoveAll(char target) {
	RemoveAll(std::to_wstring(target)[0]);
}
void text::RemoveAll(wchar_t wtarget) {
	std::wstring temp = L"";
	for (auto& wc : m_wstr) {
		if (wc == wtarget) { continue; }
		temp += wc;
	}
	m_wstr = temp;
	Length = m_wstr.length();
	return;
}

