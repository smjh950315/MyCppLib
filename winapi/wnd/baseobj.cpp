#include "baseobj.hpp"
using cyh::winapi::wnd::BaseObj;

void BaseObj::set_view_cfg(int x, int y, int w, int h) {
	X = x, Y = y, W = w, H = h;
}
void BaseObj::set_view_title(text title) {
	ObjTitle = title;
}
BaseObj::BaseObj() {}
BaseObj::BaseObj(ObjType type,int x, int y, int w, int h, text title) {
	set_view_cfg(x, y, w, h);
	set_view_title(title);
	TYPE = type;
}
BaseObj::BaseObj(ObjType type, ObjView v) {
	set_view_cfg(v.X, v.Y, v.W, v.H);
	TYPE = type;	
}
BaseObj::BaseObj(ObjType obj_type, int x, int y, int w, int h) {
	set_view_cfg(x, y, w, h);
	TYPE = obj_type;
}
BaseObj::BaseObj(ObjType obj_type, HWND* ptr_obj_handler, int x, int y, int w, int h) {
	set_view_cfg(x, y, w, h);
	hWnd = ptr_obj_handler;
	TYPE = obj_type;
}
void BaseObj::SetPos(int x, int y) {
	X = x, Y = y;
}
void BaseObj::SetSize(int w, int h) {
	W = w, H = h;
}
void BaseObj::SetHMenu(int hmenu) {
	hMenu = hmenu;
}
void BaseObj::SetHandler(HWND* hwndPtr) {
	hWnd = hwndPtr;
}
void BaseObj::SetTitle(text title) {
	set_view_title(title);
}

