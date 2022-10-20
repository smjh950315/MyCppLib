#pragma once
#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>
#include <chrono>
#include "../thirdpartylib.hpp"
#include "text.hpp"
namespace fs = ghc::filesystem;
using cyh::data::text;
namespace cyh::data {
	class DateTime {
	public:
		text Year;
		text Month;
		text Date;
		text Day;
		text Hour;
		text Minute;
		text Second;
		text DayInWeek;
		std::chrono::system_clock::time_point TimePoint;
		fs::file_time_type FTime;
		time_t TimeT;
		DateTime() { time(&TimeT); }
		text ToText(text expression) {
			text result = "";
			vector<text> piece = expression.Splits("%");
			for (auto& t : piece) {
				string additional = "";
				if (t.Length > 1) {
					additional = t.ToStr().substr(1);
				}
				switch (t.ToStr()[0])
				{
				case 'Y':
					result += Year + additional;
					break;
				case 'M':
					result += Month + additional;
					break;
				case 'D':
					result += Date + additional;
					break;
				case 'h':
					result += Hour + additional;
					break;
				case 'm':
					result += Minute + additional;
					break;
				case 's':
					result += Second + additional;
					break;
				default:
					break;
				}
			}
			return result;
		}
	};
}

#endif // !DATETIME_H
