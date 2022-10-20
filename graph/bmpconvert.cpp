#include "bmpconvert.hpp"
using cyh::graph::BmpConvert;

U8C1 BmpConvert::To8bit(U8C3 u8c3) {
	int cSum = u8c3.r + u8c3.g + u8c3.b;
	unsigned w = (unsigned)((float)cSum / 3);
	return U8C1(w);
}
void BmpConvert::MatToPhalanx(MChMat& P, Mat& m) {
	int w = m.cols;
	int h = m.rows;
	int d = m.channels();
	P = MChMat(w, h, d);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int c = 0; c < d; c++) {
				P[c][j][i] = m.at<Vec3b>(j, i)[c];
			}
		}
	}
}
void BmpConvert::PhalanxToMat(Mat& m, MChMat& P) {
	size_t w = P.Width;
	size_t h = P.Height;
	size_t d = P.Depth;
	m = cv::Mat((int)w, (int)h, CV_8UC3);
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			for (size_t c = 0; c < d; c++) {
				m.at<Vec3b>((int)i, (int)j)[c] = P[c][i][j];
			}
		}
	}
}
Bitmap BmpConvert::MatToGdiBitmap(cv::Mat& mat) {
	cv::Mat mout;
	if (mat.channels() == 3) {
		cv::cvtColor(mat, mout, cv::COLOR_BGR2BGRA);
	}
	cv::Size size = mat.size();
	return Gdiplus::Bitmap((INT)size.width, (INT)size.height, mat.step1(), PixelFormat24bppRGB, mat.data);
}