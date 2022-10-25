#include "baseobj.hpp"
using cyh::winapi::wnd::WndLayout;
using cyh::winapi::wnd::BaseObj;


void WndLayout::set(int x, int y, int w, int h, text title, int res_id) {
	X = x, Y = y, W = w, H = h;
	Title = title;
	ResourceId = res_id;
}
WndLayout::WndLayout() {
	set(0, 0, 0, 0, "", 0);
}
WndLayout::WndLayout(ObjSize s, int x, int y, text title, int res_id) {
	set(x, y, s.W, s.H, title, res_id);
}
WndLayout::WndLayout(int x, int y, int w, int h, text title, int res_id) {
	set(x, y, w, h, title, res_id);
}
void BaseObj::set_view_cfg(int x, int y, int w, int h) {
	Layout.X = x, Layout.Y = y, Layout.W = w, Layout.H = h;
}
void BaseObj::set_view_cfg(WndLayout& v) {
	set_view_cfg(v.X, v.Y, v.W, v.H);
}
void BaseObj::set_view_cfg(ObjSize& s, int x, int y) {
	set_view_cfg(x, y, s.W, s.H);
}
void BaseObj::set_view_title(text& title) {
	Layout.Title = title;
}
void BaseObj::set_handler(HWND*& obj_handler) {
	HObj = obj_handler;
}
void BaseObj::set_obj_type(ObjType& type) {
	TYPE = type;
}
void BaseObj::set_obj_res_id(int res_id) {
	Layout.ResourceId = res_id;
}
void BaseObj::set(WndLayout _layout, HWND* hObj) {
	Layout = _layout, HObj = hObj;
}
BaseObj::BaseObj() {}
