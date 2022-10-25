#include "wndobj.hpp"
using namespace cyh::winapi::wnd;

Button::Button(WndLayout _layout, HWND* hWnd) {
	set(_layout, hWnd);
	TYPE = BaseType.Button;
}
Button::Button(ObjSize size, int x, int y, text title, HWND* hWnd,int res_id) {
	WndLayout l = WndLayout(size, x, y, title,res_id);
	set(l, hWnd);
	TYPE = BaseType.Button;
}
TextBox::TextBox(WndLayout _layout, HWND* hWnd) {
	set(_layout, hWnd);
	TYPE = BaseType.MultiLineTextInput;
}
TextBox::TextBox(ObjSize size, int x, int y, HWND* hWnd, int res_id) {
	WndLayout l = WndLayout(size, x, y, "", res_id);
	set(l, hWnd);
	TYPE = BaseType.MultiLineTextInput;
}
TextDisplay::TextDisplay(WndLayout _layout, HWND* hWnd) {
	set(_layout, hWnd);
	TYPE = BaseType.MultiLineDisplayRegion;
}
TextDisplay::TextDisplay(ObjSize size, int x, int y, HWND* hWnd, int res_id) {
	WndLayout l = WndLayout(size, x, y, "", res_id);
	set(l, hWnd);
	TYPE = BaseType.MultiLineDisplayRegion;
}