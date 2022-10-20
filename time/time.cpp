#include "time.hpp"
using cyh::data::DateTime;
using cyh::Time::Time;

text Time::_decimal(text input, size_t _count) {
	text result = "-1";
	if (input == " 1") { result = "01"; }
	if (input == " 2") { result = "02"; }
	if (input == " 3") { result = "03"; }
	if (input == " 4") { result = "04"; }
	if (input == " 5") { result = "05"; }
	if (input == " 6") { result = "06"; }
	if (input == " 7") { result = "07"; }
	if (input == " 8") { result = "08"; }
	if (input == " 9") { result = "09"; }
	if (result == "-1") { result = input; }
	return result;
}
text Time::_month_to_digit(text _month) {
	string result;
	month b;
	(unsigned int)b;
	if (_month == "Jan") { result = "01"; };
	if (_month == "Feb") { result = "02"; };
	if (_month == "Mar") { result = "03"; };
	if (_month == "Apr") { result = "04"; };
	if (_month == "May") { result = "05"; };
	if (_month == "Jun") { result = "06"; };
	if (_month == "Jul") { result = "07"; };
	if (_month == "Aug") { result = "08"; };
	if (_month == "Sep") { result = "09"; };
	if (_month == "Oct") { result = "10"; };
	if (_month == "Nov") { result = "11"; };
	if (_month == "Dec") { result = "12"; };
	return result;
}
DateTime Time::_str_to_datetime(text tStr) {
	string temp = tStr.ToStr();
	DateTime dt;
	dt.Year = temp.substr(20, 4); //20~23
	dt.Month = _month_to_digit(temp.substr(4, 3)); //4~6
	dt.Date = _decimal(temp.substr(8, 2), 2); //8~9
	dt.DayInWeek = temp.substr(0, 3); //0~2
	dt.Hour = temp.substr(11, 2); //11~12
	dt.Minute = temp.substr(14, 2); //14~15
	dt.Second = temp.substr(17, 2); //17~18
	return dt;
}

DateTime Time::ToDateTime(time_t& _timet) {
	string timeStr = std::asctime(std::localtime(&_timet));
	return _str_to_datetime(timeStr);
}
DateTime Time::ToDateTime(fs::file_time_type& ftt) {
	system_clock::time_point TimePoint = std::chrono::clock_cast<std::chrono::system_clock>(ftt);
	time_t timeT = std::chrono::system_clock::to_time_t(TimePoint);
	return ToDateTime(timeT);
}
DateTime Time::LastWriteTime(text fpath) {
	fs::file_time_type fTime = fs::last_write_time(fpath.ToStr());
	system_clock::time_point TimePoint = std::chrono::clock_cast<std::chrono::system_clock>(fTime);
	time_t timeT = std::chrono::system_clock::to_time_t(TimePoint);
	return ToDateTime(timeT);
}
DateTime Time::Now() {
	time_t now;
	time(&now);
	return ToDateTime(now);
}
double Time::ToDigit(DateTime dt) {
	text digT = dt.Year + dt.Month + dt.Date + dt.Hour + dt.Minute + dt.Second;
	return digT.ToDouble();
}