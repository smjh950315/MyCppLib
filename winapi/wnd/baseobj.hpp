#pragma once
#ifndef CYH_WND_BASE_OBJ_H
#define CYH_WND_BASE_OBJ_H
#include "../header.hpp"
#include "objtype.hpp"
namespace cyh::winapi::wnd {

	class ObjSize {
	public:
		int W, H;
	};
	class WndLayout : public ObjSize {
	protected:
		void set(int x, int y, int w, int h, text title, int res_id);
	public:		
		int X, Y;
		text Title;
		int ResourceId;
		WndLayout();
		WndLayout(ObjSize _size, int x, int y, text title);
		WndLayout(ObjSize _size, int x, int y, text title, int res_id);
		WndLayout(int x, int y, int w, int h, text title, int res_id);
	};
	class BaseObj {
	protected:
		void set_view_cfg(int x, int y, int w, int h);
		void set_view_cfg(WndLayout& layout);
		void set_view_cfg(ObjSize& layout, int x, int y);
		void set_view_title(text& _title);
		void set_handler(HWND*& obj_handler);
		void set_obj_type(ObjType& type);
		void set_obj_res_id(int res_id);
		void set(WndLayout _layout, HWND* hObj);
	public:
		WndObjType BaseType;
		HWND* HObj = nullptr;
		vector<text> ObjText;
		ObjType TYPE;
		WndLayout Layout;
		BaseObj();
		operator long() { return TYPE.Id; }
	};
}
#endif

