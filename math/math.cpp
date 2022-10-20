#include "math.hpp"
using cyh::math::Compute;

Number Compute::Sigma(Number* arrA, Number* arrB, int _count) {
	Number n = 0;
	for (int i = 0; i < _count; i++) {
		n += (*(arrA + i)) * (*(arrB + i));
	}
	return n;
}
Number Compute::Sigmoid(Number x) {
	Number m = 0;
	Number E = Number::euler;
	m = Number(1) / (E ^ (-x) + 1);
	return m;
}
Number Compute::Sum(Vector<Number>& nums) {
	Number m = 0;
	for (int i = 0; i < nums.Length; i++) {
		m += nums[i];
	}
	return m;
}
Number Compute::Mean(Vector<Number>& nums) {
	Number m = Sum(nums);
	m /= (double)nums.Length;
	return m;
}


Vector<Number> Compute::Simplex(double (*F)(Vector<Number>&), SimplexParameters& params) {
	Matrix<Number> x(params.DOF, params.NoVertices);
	Vector<Number> Score(params.NoVertices);
	Vector<Number> Answer(params.DOF), Temp(params.DOF);
	Vector<Number> xH(params.DOF), xL(params.DOF), xC(params.DOF), xR(params.DOF), xB(params.DOF), xE(params.DOF);
	double FxH, FxL, FxC, FxR, FxB, FxE;
	int H, L, i, Count = 0;
	double Q = 2.0 * Number::epsilon;
	srand(int(time(0)));
	return Answer;
}