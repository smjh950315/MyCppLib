//#include <iostream>
//#include <cmath>
//#include "DataType/DataType.hpp"
//#include "Graph/Shape.hpp"
//#include "Graph/Graph.hpp"
//#include "Time/Time.hpp"
//#include "MultiThread.hpp"
//using namespace Graph;
//using namespace MultiThread;
//#include "FileSystem/Directory.hpp"
//#include "Time/Time.hpp"
//#include <cassert>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//using Data::Text;
//using Data::Vector;
//using Data::Matrix;
//using Data::Phalanx;
//using Graph::Rectangle;
//using FileSystem::File;
//using FileSystem::Directory;
//using namespace TimeUtilities;
//using cv::Mat;
//
//int sizeX = 1600;
//int sizeY = 900;
//BITMAP bmp;
//int nChannels;
//int len;
//bool isCreated = false;
//cv::Mat src;
//cv::Mat dst;
//
//void Screen();
//void HBitmapToMat(HBITMAP& _hBmp, cv::Mat& _mat);
//HBITMAP hBmp;
//HBITMAP hOld;
//int main()
//{
//	Timer t;
//	while (1) {
//		Screen();
//		HBitmapToMat(hBmp, src);
//		resize(src, dst, cv::Size(sizeX, sizeY));
//		cv::imshow("dist", dst);
//		DeleteObject(hBmp);
//		cv::waitKey(200);
//	}
//	system("pause");
//}
//void Screen() {
//	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
//	HDC hCompDC = CreateCompatibleDC(hScreen);
//
//	int nWidth = GetSystemMetrics(SM_CXSCREEN);
//	int nHeight = GetSystemMetrics(SM_CYSCREEN);
//
//	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);
//	hOld = (HBITMAP)SelectObject(hCompDC, hBmp);
//
//	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
//	SelectObject(hCompDC, hOld);
//
//	DeleteDC(hScreen);
//	DeleteDC(hCompDC);
//}
//
//void HBitmapToMat(HBITMAP& _hBmp, cv::Mat& _mat) {
//
//	GetObject(_hBmp, sizeof(BITMAP), &bmp);
//	if (!isCreated) {
//		nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
//		len = bmp.bmHeight * bmp.bmWidth * nChannels;
//		_mat.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
//	}
//
//	GetBitmapBits(_hBmp, len, _mat.data);
//	isCreated = true;
//}
//
