#pragma once
#ifndef SIMPLEX_PARAM_H
#define SIMPLEX_PARAM_H
namespace cyh::math {
	struct SimplexParameters {
		//ºû«×
		const int DOF = 2;
		const int MaxCount = 1000;
		//Q­È¤U­­
		const double eps = 1e-20;
		const double Alpha = 1.0;
		const double Beta = 0.5;
		const double Gamma = 2.0;
		const double Range = 5.0;
		const double NoVertices = DOF + 1;
	};
}
#endif