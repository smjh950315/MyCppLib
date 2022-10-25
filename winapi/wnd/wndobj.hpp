#pragma once
#ifndef WINDOW_OBJECT_H
#define WINDOW_OBJECT_H
#include "baseobj.hpp"
using cyh::winapi::wnd::BaseObj;

namespace cyh::winapi::wnd {

	class Button : public BaseObj {
	public:
		Button(WndLayout _layout, HWND* hWnd);
		Button(ObjSize _size, int x, int y, text title, HWND* hWnd, int res_id);
	};

	class TextBox :public BaseObj {
	protected:
	public:
		size_t MaxLength = INT_MAX;
		text Text;
		TextBox(WndLayout _layout, HWND* hWnd);
		TextBox(ObjSize _size, int x, int y, HWND* hWnd, int res_id);
	};

	class TextDisplay :public BaseObj {
	protected:
	public:
		size_t MaxLength = INT_MAX;
		text Text;
		TextDisplay(WndLayout _layout, HWND* hWnd);
		TextDisplay(ObjSize _size, int x, int y, HWND* hWnd, int res_id);
	};



}
#endif // !WINDOW_OBJECT_H
