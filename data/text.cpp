#include "convert.hpp"
#include "text.hpp"
using Convert = cyh::Convert;
using cyh::data::text;

void text::_clear() {
	this->_str.clear();
	Length = _str.length();
}
void text::_set(int n) {
	this->_str = std::to_wstring(n);
	Length = _str.length();
}
void text::_set(double n) {
	this->_str = std::to_wstring(n);
	Length = _str.length();
}
void text::_set(char c) {
	this->_str = std::to_wstring(c);
	Length = _str.length();
}
void text::_set(wchar_t c) {
	this->_str = c;
	Length = _str.length();
}

void text::_set(string str) {
	this->_str = cyh::Convert::ToWideStr(str);
	Length = _str.length();
}
void text::_set(std::wstring str) {
	this->_str = str;
	Length = _str.length();
}

void text::_add(const int n) {
	_str += std::to_wstring(n);
	Length += 1;
}
void text::_add(const double n) {
	_str += std::to_wstring(n);
	Length += 1;
}
void text::_add(const char c) {
	_str += std::to_wstring(c);
	Length += 1;
}
void text::_add(const wchar_t c) {
	_str += c;
	Length += 1;
}
void text::_add(string str) {
	_str += cyh::Convert::ToWideStr(str);
	Length += str.length();
}
void text::_add(std::wstring str) {
	this->_str += str;
	Length += str.length();
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
	size_t iStart = _str.find(cyh::Convert::ToWideStr(s), startIndex);
	if (iStart == string::npos) {
		return -1;
	}
	return iStart;
}
size_t text::_findIndexEndFrom(size_t startIndex, string s) {
	size_t iStart = _str.find(cyh::Convert::ToWideStr(s), startIndex);
	if (iStart == string::npos) {
		return -1;
	}
	return iStart + s.length() - 1;
}
text text::_splitProcess(size_t idStart, text sStart, text sEnd, size_t* iReserve) {
	if (idStart + 1 > Length) { return L""; }
	size_t minTotLen = idStart + sStart.Length + sEnd.Length;
	if (minTotLen >= Length) { return L""; }
	size_t iStart = _findIndexEndFrom(idStart, sStart);
	size_t iEnd = _findIndexStartFrom(iStart, sEnd);
	*iReserve = iEnd - 1;
	return _subStr(iStart + 1, iEnd - 1);
}
text text::_subStr(size_t iStart, size_t iEnd) {
	//if (!_rangeValid(iStart, iEnd)) { return L""; }
	//return _str.substr(iStart, iEnd - iStart + 1);
	if (!_rangeValid(iStart, iEnd - 1)) { return L""; }
	return _str.substr(iStart, iEnd - iStart);
}
text::text(vector<text> v) {
	_clear();
	for (auto& s : v) {
		_add(s._str);
	}
}

text::operator std::string() {
	return cyh::Convert::ToNarrowStr(_str);
}
text::operator std::wstring() {
	return this->_str;
}
double text::ToDouble() {
	return atoi(cyh::Convert::ToNarrowStr(_str).c_str());
}
std::string text::ToStr() {
	return cyh::Convert::ToNarrowStr(_str);
}
std::wstring text::ToWStr() {
	return _str;
}
text::operator const char* () {
	string temp = cyh::Convert::ToNarrowStr(_str);
	char* chptr = new char[Length + 1];
	for (int i = 0; i < Length; i++) {
		chptr[i] = temp[i];
	}
	chptr[Length] = '\0';
	return chptr;
}
text::operator const wchar_t* () {
	return (this->_str).c_str();
}
text::operator LPWSTR () {
	return (wchar_t*)((this->_str).c_str());
}
wchar_t text::operator[](size_t i) {
	if (i < Length) {
		return _str[i];
	}
	return ' ';
}

text text::operator+(const int& n) {
	text _temp = _str;
	_temp._add(n);
	return _temp;
}
text text::operator+(const double& n) {
	text _temp = _str;
	_temp._add(n);
	return _temp;
}
text text::operator+(const char& c) {
	text _temp = _str;
	_temp._add(c);
	return _temp;
}
text text::operator+(const wchar_t& c) {
	text _temp = _str;
	_temp._add(c);
	return _temp;
}
text text::operator+(const char* c) {
	text _temp = _str;
	_temp._add(c);
	return _temp;
}
text text::operator+(const wchar_t* c) {
	text _temp = _str;
	_temp._add(c);
	return _temp;
}
text text::operator+(const string& str) {
	text _temp = _str;
	_temp._add(str);
	return _temp;
}
text text::operator+(const wstring& str) {
	text _temp = _str;
	_temp._add(str);
	return _temp;
}
text text::operator+(const text& str) {
	text _temp = _str;
	_temp._add(str._str);
	return _temp;
}
text text::operator+(const vector<text>& v) {
	text _temp = _str;
	for (auto& s : v) {
		_temp._add(s._str);
	}
	return _temp;
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
	_set(str);
	return *this;
}
text& text::operator=(const wchar_t* chptr) {
	std::wstring wstr = chptr;
	_set(wstr);
	return *this;
}
text& text::operator=(const string& str) {
	_set(str);
	return *this;
}
text& text::operator=(const wstring& str) {
	_set(str);
	return *this;
}
text& text::operator=(const text& str) {
	_set(str._str);
	return *this;
}
text& text::operator=(const vector<text>& v) {
	_clear();
	for (auto& s : v) {
		_add(s._str);
	}
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
	_add(str);
	Length = _str.length();
	return *this;
}
text& text::operator+=(const wstring& str) {
	_add(str);
	Length = _str.length();
	return *this;
}
text& text::operator+=(const text& str) {
	_add(str._str);
	Length = _str.length();
	return *this;
}
text& text::operator+=(const vector<text>& v) {
	for (auto& s : v) {
		_add(s._str);
	}
	return *this;
}

bool text::operator == (const double& n) {
	wstring wstr = cyh::Convert::ToWideStr(std::to_string(n)); return _str == wstr;
}
bool text::operator != (const double& n) {
	wstring wstr = cyh::Convert::ToWideStr(std::to_string(n)); return _str != wstr;
}
bool text::operator == (const char& c) {
	if (Length != 1) { return false; }
	string str = "" + c;
	return _str == cyh::Convert::ToWideStr(str);
}
bool text::operator != (const char& c) {
	if (Length != 1) { return true; }
	string str = "" + c;
	return _str != cyh::Convert::ToWideStr(str);
}
bool text::operator == (const wchar_t& c) {
	if (Length != 1) { return false; }
	string str = "" + c;
	return _str[0] == c;
}
bool text::operator != (const wchar_t& c) {
	if (Length != 1) { return true; }
	string str = "" + c;
	return _str[0] != c;
}
bool text::operator == (const char* chptr)
{
	return _str == cyh::Convert::ToWideStr(chptr);
}
bool text::operator != (const char* chptr) {
	return _str != cyh::Convert::ToWideStr(chptr);
}
bool text::operator == (const wchar_t* chptr)
{
	return _str == chptr;
}
bool text::operator != (const wchar_t* chptr) {
	return _str != chptr;
}
bool text::operator == (const string& str) {
	return _str == cyh::Convert::ToWideStr(str);
}
bool text::operator != (const string& str) {
	return _str != cyh::Convert::ToWideStr(str);
}
bool text::operator == (const text& text) {
	return _str == text._str;
}
bool text::operator != (const text& text) {
	return _str != text._str;
}

bool text::Contain(text t) {
	size_t i = _str.find(t._str);
	if (i != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}
bool text::IsBetween(text t) {
	if (_str.starts_with(t._str) && _str.ends_with(t._str)) {
		return true;
	}
	return false;
}
size_t text::CountOf(text t) {
	int _count = 0;
	size_t iStart = 0;
	while (1) {
		size_t iFind = _findIndexEndFrom(iStart, t);
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
	return _findIndexEndFrom(iStart, t);
}
size_t text::FirstIndexOf(text t) {
	size_t iFind = -1;;
	iFind = _findIndexStartFrom(0, t);
	if (iFind == std::string::npos) {
		iFind = -1;
	}
	return iFind;
}
size_t text::LastIndexOf(text t) {
	size_t iLastFound = -1;
	size_t countFind = 0;
	for (size_t iFind = 0; iFind < Length; iFind++) {
		iFind = _findIndexStartFrom(iFind, t);
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
	//return _subStr(iStart + 1, iEnd - 1);
	return _subStr(iStart + 1, iEnd);
}
text text::Between(text sStart, text sEnd) {
	return Between(0, sStart, sEnd);
}
text text::Between(size_t idStart, text sStart, text sEnd) {
	if (idStart + 1 > Length) { return ""; }
	size_t minTotLen = idStart + sStart.Length + sEnd.Length;
	if (minTotLen >= Length) { return ""; }
	size_t iStart = _findIndexEndFrom(idStart, sStart);
	size_t iEnd = _findIndexStartFrom(iStart, sEnd);
	//return _subStr(iStart + 1, iEnd - 1);
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
	size_t len = t._str.length();
	size_t iStart = 0;
	size_t iFind = 0;
	size_t iFindReserve = 0;
	size_t countFind = 0;
	while (1) {
		iFind = _str.find(t._str, iStart);
		if (iFind == wstring::npos) { break; }
		countFind++;
		text s = _str.substr(iStart, iFind - iStart);
		iStart = iFind + 1;
		if (s.Length > 0) {
			_v.push_back(s);
		}
		iFindReserve = iFind;
	}
	if (countFind == 0) {
		_v.push_back(_str);
	}
	else if (iFindReserve < Length - 1) {
		_v.push_back(SubString(iFindReserve + 1, Length));
	}
	return _v;
}
vector<text> text::GetContentEnvloped(text _envStart, text _envEnd) {
	vector<text> brContent;
	//if (!IsEnveloped(_envStart, _envEnd)) {
	//	brContent.push_back("");
	//	return brContent;
	//}
	text eS = _envStart;
	text eE = _envEnd;
	text temp = "";
	size_t countOfES = 0;
	size_t countOfEE = 0;
	for (size_t i = 0; i < Length; i++) {

		size_t fnd_s = _findIndexStartFrom(i, eS);
		if (fnd_s == -1) { break; }
		else {
			i = fnd_s;
		}
		size_t fnd_e = _findIndexStartFrom(i, eE);
		if (fnd_e == -1) { break; }
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
					fnd_e = _findIndexStartFrom(fnd_e + 1, eE);
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
	for (auto& c : _str) {
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
	return _findIndexStartFrom(0, txt) == 0;
}
bool text::EndWith(text txt) {
	return LastIndexOf(txt) + txt.Length == Length;
}
void text::FillWith(text txt, int times) {
	_str = L"";
	for (int i = 0; i < times; i++) {
		_str += txt._str;
	}
	Length = _str.length();
}
void text::Replace(text target, text result) {
	size_t iStart = _findIndexStartFrom(0, target);
	if (iStart == -1) {
		return;
	}
	_str.replace(iStart, target.Length, result._str);
	Length = _str.length();
}
void text::ReplaceAll(text target, text result) {
	size_t iStart = 0;
	while (iStart >= 0 && iStart < Length) {
		iStart = _findIndexStartFrom(0, target);
		if (iStart == std::string::npos) {
			break;
		}
		if (iStart + target.Length >= Length) {
			break;
		}
		_str.replace(iStart, target.Length, result._str);
		Length = _str.length();
	}
	return;
}
void text::AddWrapping(text text) {
	_str = text._str + _str + text._str;
}
void text::Trim() {
	int i = 0;
	while (_findIndexEndFrom(0, " ") > 0 && i + 1 < Length) {
		Replace(" ", "");
		i++;
	}
}