#pragma once
#ifndef CYH_WIN_API_H
#define CYH_WIN_API_H
#include <opencv2/opencv.hpp> 
#include "header.hpp"
#include "wnd/window.hpp"
#include "../data/tuples.hpp"
#include "../graph/graph.hpp"

namespace cyh::winapi::wnd {
	class WndApi {
	public:
		HWND hWnd;
		WndApi(HWND hwnd);
		void OnPaint(Phalanx<unsigned> ph);
		void OnSize(HWND hwnd, UINT flag, int width, int height);
		static void CreateImg(cv::Mat& mat, HDC hdc);
		static void CreateImg(text path, HDC hdc);
		void ScreenShot(HBITMAP* hBitmap, HBITMAP* holdBitmap);

		static void GetInputText(HWND hInput, text& buffer, size_t length);
		static void ShowMsgBox(HWND hWnd, text msgTitle, text msgText);
		static void ShowText(HDC hdc, int x, int y, text _text);
		static void SetText(HWND hWnd, text& _text, int hMenu);
		static void AddTextToDlg(HWND hEdit, text& _text, int hMenu);
		static void ChangeButtonText(LPARAM lparam, text& infoText);
		static void HideItem(HWND hItem);
		static void ShowItem(HWND hItem);
	};
}
namespace cyh::winapi {


}

#endif // !WIN_API_H


