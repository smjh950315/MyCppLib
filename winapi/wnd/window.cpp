#include "window.hpp"
#include "../winapi.hpp"
#include "objtype.hpp"
using WndSize = cyh::winapi::wnd::WndSize;
using WndClass = cyh::winapi::wnd::WndClass;
using Window = cyh::winapi::wnd::Window;

WndSize::WndSize() {
	Width = 100, Height = 100;
}
WndSize::WndSize(int w, int h) {
	Width = w, Height = h;
}
void WndSize::ReadSize(LPARAM lParam) {
	Width = LOWORD(lParam);
	Height = HIWORD(lParam);
}

WndClass::WndClass() {}
WndClass::WndClass(HINSTANCE _hInstance, LRESULT(*WndProc)(HWND, UINT, WPARAM, LPARAM)) {
	cbSize = sizeof(WndClass);
	style = CS_HREDRAW | CS_VREDRAW;
	lpfnWndProc = WndProc;
	cbClsExtra = 0;
	cbWndExtra = 0;
	hInstance = _hInstance;
	hIcon = LoadIcon(this->hInstance, IDI_APPLICATION);
	hCursor = LoadCursor(NULL, IDC_ARROW);
	hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	lpszMenuName = NULL;
	hIconSm = LoadIcon(this->hInstance, IDI_APPLICATION);
}


LRESULT Window::BasicWndMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//PAINTSTRUCT ps;
	//HDC hdc;
	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			LRESULT ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			TCHAR  ListItem[256];
			(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
				(WPARAM)ItemIndex, (LPARAM)ListItem);
			//MessageBox(hWnd, (LPCWSTR)ListItem, TEXT("Item Selected"), MB_OK);
			break;
		}
		switch (LOWORD(wParam))
		{
		case 9999://btn int
			break;

		default:
			break;
		}
		break;
	case WM_GETMINMAXINFO:
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;
		lpMMI->ptMaxTrackSize.x = 800;
		lpMMI->ptMaxTrackSize.y = 600;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
void Window::_ptr_initiate() {
	WndcPtr = new WndClass;
	Objects = new vector<WndObj>;
}
void Window::_wnd_register() {
	if (!IsInitialized) {
		WndReg = false;
	}
	if (!RegisterClassEx(WndcPtr))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		WndReg = false;
	}
	WndReg = true;
}
void Window::_hWnd_register() {
	if (!IsInitialized) {
		HWndReg = false;
	}
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		HWndReg = false;
	}
	HWndReg = true;
}
void Window::_setWndHandler() {

	hWnd = CreateWindowEx(
		/*WS_EX_OVERLAPPEDWINDOW | this make resizable*/
		WS_OVERLAPPED | WS_MINIMIZEBOX,
		(*WndcPtr).lpszClassName,
		WndTitle,
		(DisableResize ?
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME : WS_OVERLAPPEDWINDOW),
		CW_USEDEFAULT, CW_USEDEFAULT,
		Size.Width, Size.Height,
		NULL, NULL,
		(*WndcPtr).hInstance, NULL
	);
}
void Window::_setWndHandler(HWND* hptr) {
	*hptr = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		(*WndcPtr).lpszClassName,
		WndTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Size.Width, Size.Height,
		NULL, NULL,
		(*WndcPtr).hInstance, NULL
	);
}
void Window::_load_object() {
	for (auto& o : *Objects) {
		_obj_create(o);
	}
}
void Window::_add_option_to_dropdown_list(HWND* hCbBox,vector<text>& options) {
	for (auto& opt : options) {
		SendMessage(*hCbBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(const wchar_t*)opt);
	}
}
void Window::_obj_create(BaseObj obj) {
	if (!obj.hWnd) {
		CreateWindow(
			obj.TYPE.lpClassName,
			obj.ObjTitle,
			obj.TYPE.dwStyle,
			obj.X, obj.Y, obj.W, obj.H,
			hWnd, // Parent window
			(HMENU)(obj.hMenu), // No menu.
			*hInstance,
			NULL);
	}
	else {
		*(obj.hWnd) = CreateWindow(
			obj.TYPE.lpClassName,
			obj.ObjTitle,
			obj.TYPE.dwStyle,
			obj.X, obj.Y, obj.W, obj.H,
			hWnd, // Parent window
			(HMENU)(obj.hMenu), // No menu.
			*hInstance,
			NULL);
	}
}

Window::Window() {
	_ptr_initiate();
}
Window::Window(HINSTANCE* _hInstance, int* _nCmdShow) {
	_ptr_initiate();
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
}
void Window::Configuration(int w, int h, text wndClass, text title) {
	Size.Width=w, Size.Height=h, WndCName=wndClass, WndTitle=title;
}
void Window::SetHandlers(HINSTANCE* _hInstance, int* _nCmdShow) {
	_ptr_initiate();
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
}
void Window::SetWndProcess(LRESULT(*_WndProc)(HWND, UINT, WPARAM, LPARAM)) {
	WndProcPtr = _WndProc;
}
void Window::Build() {
	//(*WndcPtr) = WndClass(*hInstance, WndProcPtr);
	(*WndcPtr) = WndClass(*hInstance, WndProcPtr);
	(*WndcPtr).lpszClassName = WndCName;
	IsInitialized = true;
	_wnd_register();
	_setWndHandler();
	ShowWindow(hWnd, *nCmdShow);
	UpdateWindow(hWnd);
	_hWnd_register();
	_load_object();

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::AddDropdownList(WndObj drop_down_list, HWND* hParent, vector<text>& options) {
	drop_down_list.TYPE = objType.DropDownList;
	drop_down_list.hWnd = hParent;
	drop_down_list.ObjText = options;
	(*Objects).push_back(drop_down_list);
}
void Window::AddDropdownList(int x, int y, int w, int h, HWND* hParent, vector<text>& options) {
	AddDropdownList(WndObj(objType.DropDownList, x, y, w, h), hParent, options);
}

void Window::AddDisplayRegin(WndObj display_region, int hMenu) {
	display_region.TYPE = objType.MultiLineDisplayRegion;
	display_region.hMenu = hMenu;
	(*Objects).push_back(display_region);
}
void Window::AddDisplayRegin(int x, int y, int w, int h, int hMenu) {
	AddDisplayRegin(WndObj(objType.MultiLineDisplayRegion, x, y, w, h), hMenu);
}

void Window::AddInputBox(WndObj txtInput, HWND* input_hWnd) {
	txtInput.TYPE = objType.SingleLineTextInput;
	txtInput.hWnd = input_hWnd;
	(*Objects).push_back(txtInput);
}
void Window::AddInputBox(int x, int y, int w, int h, HWND* input_hWnd) {
	AddInputBox(WndObj(objType.SingleLineTextInput, x, y, w, h), input_hWnd);
}

void Window::AddInputBoxMultiLine(WndObj txtInput, HWND* input_hWnd) {
	txtInput.TYPE = objType.MultiLineTextInput;
	txtInput.hWnd = input_hWnd;
	(*Objects).push_back(txtInput);
}
void Window::AddInputBoxMultiLine(int x, int y, int w, int h, HWND* input_hWnd) {
	AddInputBoxMultiLine(WndObj(objType.MultiLineTextInput, x, y, w, h), input_hWnd);
}

void Window::AddButton(WndObj btn, int hMenu) {
	btn.TYPE = objType.Button;
	btn.hMenu = hMenu;
	(*Objects).push_back(btn);
}
void Window::AddButton(int x, int y, int w, int h, text btnTxt, int hMenu) {
	AddButton(WndObj(objType.Button, x, y, w, h, btnTxt), hMenu);
}

void Window::AddObject(ObjType type, ObjView vcfg) {
	WndObj obj(type, vcfg);
	AddObject(obj);
}
void Window::AddObject(WndObj obj) {
	Objects->push_back(obj);
}
