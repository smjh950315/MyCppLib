#pragma once
#ifndef CONVERT_GRAPH_H
#define CONVERT_GRAPH_H
#include "header.hpp"
namespace cyh::graph {
	class BmpConvert {
	private:
		using Mat = cv::Mat;
		using Vec3b = cv::Vec3b;
	public:
		static U8C1 To8bit(U8C3 u8c3);
		static void MatToPhalanx(MChMat& P, Mat& m);
		static void PhalanxToMat(Mat& m, MChMat& P);
		static Bitmap MatToGdiBitmap(cv::Mat& mat);
	};

}

#endif // !CONVERT_IMG_H
