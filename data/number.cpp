#include "number.hpp"
using cyh::data::Number;

double Number::Rand0_1() {
	srand((unsigned)time(NULL));
	double x = (double)rand() / (RAND_MAX + 1.0);
	return x;
}
double Number::RandFloat(double min, double max) {
	srand((unsigned)time(NULL));
	double x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
	return x;
}
int Number::EzRandInt(int max) {
	srand((unsigned)time(NULL));
	int x = rand() % (max + 1);
	return x;
}
int Number::EzRandInt(int min, int max) {
	srand((unsigned)time(NULL));
	int x = rand() % (max - min + 1) + min;
	return x;
}
int Number::RandInt(int max) {
	srand((unsigned)time(NULL));
	if ((max - 1) == RAND_MAX) {
		return rand();
	}
	else {
		/* 計算可以被整除的長度 */
		long end = RAND_MAX / max;
		assert(end > 0L);
		end *= max;

		/* 將尾端會造成偏差的幾個亂數去除，
		   若產生的亂數超過 limit，則將其捨去 */
		int r;
		while ((r = rand()) >= end);

		return r % max;
	}
}
int Number::RandInt(int min, int max) {
	srand((unsigned)time(NULL));
	int r = RandInt(max - min + 1) + min;
	return r;
}

Number Number::operator+(const Number& num) {
	Number n = _val + num._val;
	return n;
}
Number Number::operator-(const Number& num) {
	Number n = _val - num._val;
	return n;
}
Number Number::operator*(const Number& num) {
	Number n = _val * num._val;
	return n;
}
Number Number::operator/(const Number& num) {
	if (num._val == 0) {
		return INT_MAX;
	}
	Number n = _val / num._val;
	return n;
}
Number Number::operator^(const Number& num) {
	return pow(_val, num._val);
}

Number& Number::operator=(const Number& num) {
	_val = num._val;
	return *this;
}
Number& Number::operator+=(const Number& num) {
	_val += num._val;
	return *this;
}
Number& Number::operator-=(const Number& num) {
	_val -= num._val;
	return *this;
}
Number& Number::operator*=(const Number& num) {
	_val *= num._val;
	return *this;
}
Number& Number::operator/=(const Number& num) {
	if (num._val == 0) {
		_val = DBL_MAX;
	}
	_val /= num._val;
	return *this;
}
Number& Number::operator^=(const Number& num) {
	_val = pow(_val, num._val);
	return *this;
}

bool Number::operator==(const Number& num) {
	return _val == num._val;
}
bool Number::operator!=(const Number& num) {
	return _val != num._val;
}