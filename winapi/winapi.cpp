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

	//建立handler
	HDC hScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//建立適合hSrceen的handler
	HDC hCompatible = CreateCompatibleDC(hScreen);
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);

	//用handler 跟 W H 建立點陣圖
	(*hBmp) = CreateCompatibleBitmap(hScreen, nWidth, nHeight);

	//將hBitmap轉換到適合hCompatible的HGDIOBJ 後將HDC傳入holdbmp
	(*holdBmp) = (HBITMAP)SelectObject(hCompatible, *hBmp);

	SelectObject(hCompatible, (*holdBmp));

	BitBlt(hCompatible, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);
	DeleteDC(hScreen);
	DeleteDC(hCompatible);
}


void WndApi::ShowMsgBox(HWND hWnd, text msgTitle, text msgText) {
	MessageBox(hWnd, msgText, msgTitle, MB_OK | MB_ICONINFORMATION);
}
void WndApi::ShowText(HDC hdc, int x, int y, text _text) {
	const wchar_t* txt = (const wchar_t*)_text;
	TextOut(hdc, x, y, txt, (int)_text.Length);
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


void WndApi::GetText(TextBox* tb) {
	size_t txtLen = GetWindowTextLength(*tb->HObj) + 1;
	tb->Text = text(' ', txtLen);
	GetWindowText(*tb->HObj, tb->Text, (int)txtLen);
}
void WndApi::SetText(TextDisplay* tb, text txt) {
	SetWindowText(*tb->HObj, txt);
}
HFONT WndApi::BasicFont(int _height) {
	return CreateFontW(_height, 0, 0, 0, 400,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FIXED_PITCH, TEXT("Consolas")
	);
}
HFONT WndApi::CustomFont(int _height, text _font) {
	return CreateFontW(_height, 0, 0, 0, 400,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FIXED_PITCH, _font
	);
}
void WndApi::SetItemFont(BaseObj* item, HFONT _font) {
	SendMessage(*item->HObj, WM_SETFONT, (WPARAM)_font, NULL);
}

