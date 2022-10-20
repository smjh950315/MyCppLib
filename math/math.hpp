#pragma once
#ifndef MATH_H
#define MATH_H
#include "../data/number.hpp"
#include "../data/tuples.hpp"
#include "simplexparameter.hpp"
using cyh::data::Number;
using cyh::data::Vector;
using cyh::data::Matrix;
namespace cyh::math {
	class Compute {
	public:
		static Number Sigma(Number* arrA, Number* arrB, int _count);
		static Number Sigmoid(Number x);
		static Number Sum(Vector<Number>& nums);
		static Number Mean(Vector<Number>& nums);
		static Vector<Number> Simplex(double (*F)(Vector<Number>&), SimplexParameters& param);
	
	
	};

}
#endif // !MATH_H
