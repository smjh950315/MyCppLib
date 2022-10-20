#include "winapi.hpp"
using namespace cyh::winapi::wnd;

WndApi::WndApi(HWND hwnd) {
	hWnd = hwnd;
}
void WndApi::OnPaint(Phalanx<unsigned> ph) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	//Paint
	EndPaint(hWnd, &ps);
}
void WndApi::OnSize(HWND hwnd, UINT flag, int width, int height) {

}
void WndApi::CreateImg(cv::Mat& mat, HDC hdc) {
	Mat mout;
	Graphics graphics(hdc);
	if (mat.channels() == 1) {
		cv::cvtColor(mat, mout, cv::COLOR_GRAY2BGRA);
	}
	if (mat.channels() == 3) {
		cv::cvtColor(mat, mout, cv::COLOR_BGR2BGRA);
	}
	Bitmap img = GConvert::MatToGdiBitmap(mat);
	graphics.DrawImage(&img, 0, 0);
}
void WndApi::CreateImg(text path, HDC hdc) {
	Mat mat = cv::imread(path);
	Mat mout;
	Graphics graphics(hdc);
	if (mat.channels() == 1) {
		cv::cvtColor(mat, mout, cv::COLOR_GRAY2BGRA);
	}
	if (mat.channels() == 3) {
		cv::cvtColor(mat, mout, cv::COLOR_BGR2BGRA);
	}
	Bitmap img = GConvert::MatToGdiBitmap(mat);
	graphics.DrawImage(&img, 0, 0);
}
void WndApi::ScreenShot(HBITMAP* hBmp, HBITMAP* holdBmp) {

	//�إ�handler
	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//�إ߾A�XhSrceen��handler
	HDC hCompatible = CreateCompatibleDC(hScreen);
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);

	//��handler �� W H �إ��I�}��
	(*hBmp) = CreateCompatibleBitmap(hScreen, nWidth, nHeight);

	//�NhBitmap�ഫ��A�XhCompatible��HGDIOBJ ��NHDC�ǤJholdbmp
	(*holdBmp) = (HBITMAP)SelectObject(hCompatible, *hBmp);

	SelectObject(hCompatible, (*holdBmp));

	BitBlt(hCompatible, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
	DeleteDC(hScreen);
	DeleteDC(hCompatible);
}




void WndApi::GetInputText(HWND hInput, text& buffer, size_t length) {
	GetWindowText(hInput, buffer, (int)length);
}
void WndApi::ShowMsgBox(HWND hWnd, text msgTitle, text msgText) {
	MessageBox(hWnd, msgText, msgTitle, MB_OK | MB_ICONINFORMATION);
}
void WndApi::ShowText(HDC hdc, int x, int y, text _text) {
	const wchar_t* txt = (const wchar_t*)_text;
	TextOut(hdc, x, y, txt, (int)_text.Length);
}
void WndApi::SetText(HWND hWnd, text& _text, int hMenu) {
	const wchar_t* txt = (const wchar_t*)_text;
	SetDlgItemText(hWnd, hMenu, txt);
}
void WndApi::AddTextToDlg(HWND hEdit, text& _text, int hMenu) {
	const wchar_t* txt = (const wchar_t*)_text;
	size_t TextLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(hEdit, EM_SETSEL, (WPARAM)TextLen, (LPARAM)TextLen);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)txt);
}
void WndApi::ChangeButtonText(LPARAM lparam, text& infoText) {
	SendMessage((HWND)lparam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)(const wchar_t*)infoText);
}
void WndApi::HideItem(HWND hItem) {
	ShowWindow(hItem, SW_HIDE);
}
void WndApi::ShowItem(HWND hItem) {
	ShowWindow(hItem, SW_SHOW);
}