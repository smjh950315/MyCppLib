#pragma once
#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <cmath>
#include <float.h>
#include "convert.hpp"
namespace cyh::data {
	class Number {
	private:
		double _val = 0;
	public:	
		static double Rand0_1();
		static double RandFloat(double min, double max);
		static int EzRandInt(int max);
		static int EzRandInt(int min, int max);
		static int RandInt(int max);
		static int RandInt(int min, int max);
		static inline constexpr double PI = 3.1415926;
		static inline constexpr double euler = 2.7182818;
		static inline constexpr double epsilon = 1e-20;
		
		Number() { std::string::npos; }
		Number(int i) :_val(i) {}
		Number(float f) :_val(f) {}
		Number(double d) :_val(d) {}
		Number(const Number& d) :_val(d._val) {}

		double ToDouble() { return _val; }
		operator double() { return _val; }
		Number operator+(const Number& num);
		Number operator-(const Number& num);
		Number operator*(const Number& num);
		Number operator/(const Number& num);
		Number operator^(const Number& num); 

		Number& operator=(const Number& num);
		Number& operator+=(const Number& num);
		Number& operator-=(const Number& num);
		Number& operator*=(const Number& num);
		Number& operator/=(const Number& num);
		Number& operator^=(const Number& num);

		bool operator==(const Number& num);
		bool operator!=(const Number& num);
	};
}
#endif // !NUMBER_H


