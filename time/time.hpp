#pragma once
#ifndef TIMEUTITIES_H
#define TIMEUTITIES_H
#include <chrono>
#include "../includelist.h"
#include "../data/text.hpp"
#include "../data/datetime.hpp"
using cyh::data::text;
using cyh::data::DateTime;
namespace fs = ghc::filesystem;
using namespace std::chrono;
namespace cyh::Time {
	class Time {
	private:
		static text _decimal(text input, size_t _count);
		static text _month_to_digit(text _month);
		static DateTime _str_to_datetime(text time_t_str);
	public:
		static DateTime ToDateTime(time_t& _timet);
		static DateTime ToDateTime(fs::file_time_type& ftt);
		static DateTime LastWriteTime(text _path);
		static DateTime Now();
		static double ToDigit(DateTime dt);
	};
	class Timer {
	private:
	public:
		LARGE_INTEGER t1 = {};
		LARGE_INTEGER t2 = {};
		LARGE_INTEGER freq = {};
		LARGE_INTEGER DuraMicroSec = {};
		Timer() {
			t1.QuadPart = 0;
			QueryPerformanceFrequency(&freq);
		}
		~Timer() {}
		void Start() {
			QueryPerformanceCounter(&t1);
		}
		void End() {
			QueryPerformanceCounter(&t2);
			DuraMicroSec.QuadPart = t2.QuadPart - t1.QuadPart;
		}
		void Clear() {
			DuraMicroSec.QuadPart = 0;
		}

		long double DurationSec() {
			return long double(DuraMicroSec.QuadPart) / freq.QuadPart;
		}
		long double DurationMilli() {

			return DurationSec() * 1000;
		}
		long double DurationMicro() {
			return DurationMilli() * 1000;
		}

		text DSecondStr() {
			text dSecond = (double)DurationSec();
			dSecond += " sec";
			return dSecond;
		}
		text DMilliStr() {
			text dSecond = (double)DurationMilli();
			dSecond += " ms";
			return dSecond;
		}
		text DMicroStr() {
			text dSecond = (double)DurationMicro();
			dSecond += " us";
			return dSecond;
		}
	};
}
#endif // !TIME_H
