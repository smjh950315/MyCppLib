#pragma once
#ifndef MATH_H
#define MATH_H
#include "../data/number.hpp"
#include "../data/tuples.hpp"
#include "polynomial.hpp"
#include "simplexparameter.hpp"
using cyh::data::Number;
using cyh::data::Vector;
using cyh::data::Matrix;
using cyh::math::Polynomial;
namespace cyh::math {
	class Compute {
	public:
		static Number Sigma(Number* arrA, Number* arrB, int _count);
		static Number Sigmoid(Number x);
		static Number Sum(Vector<Number>& nums);
		static Number Mean(Vector<Number>& nums);
		static Vector<Number> Simplex(double (*F)(Vector<Number>&), SimplexParameters& param);

	};
	class Calculus {
	public:
		static Polynomial Derivative(Polynomial _func);
		static Polynomial Integral(Polynomial _func);
	};
}
#endif // !MATH_H
