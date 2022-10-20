#pragma once
#ifndef CYH_WND_BASE_OBJ_H
#define CYH_WND_BASE_OBJ_H
#include "../header.hpp"
#include "objtype.hpp"
namespace cyh::winapi::wnd {
	struct ObjPos {
		int X, Y;
		ObjPos() :X(0), Y(0) {}
		ObjPos(int x, int y) :X(x), Y(y) {}
	};
	struct ObjSize {
		int W, H;
		ObjSize() :W(100), H(100) {}
		ObjSize(int w, int h) :W(w), H(h) {}
		void Read(LPARAM lParam) {
			W = LOWORD(lParam);
			H = HIWORD(lParam);
		}
	};
	struct ObjView : public ObjPos, public ObjSize {
		text ObjTitle = "";
		ObjView() {}
		ObjView(int x, int y, int w, int h)
		{
			X = x, Y = y, W = w, H = w;
		}
	};
	struct ObjData {
		HWND* hWnd = nullptr;		
		vector<text> ObjText;
		int hMenu = 0;
		ObjData() {}
	};

	class BaseObj : public ObjView, public ObjData {
	protected:
		void set_view_cfg(int x, int y, int w, int h);
		void set_view_title(text _title);
	public:
		ObjType TYPE;
		BaseObj();
		BaseObj(ObjType obj_type, ObjView view);
		BaseObj(ObjType obj_type, int x, int y, int w, int h);
		BaseObj(ObjType obj_type, int x, int y, int w, int h, text _title);
		BaseObj(ObjType obj_type, HWND* ptr_obj_handler, int x, int y, int w, int h);
		void SetPos(int x, int y);
		void SetSize(int w, int h);
		void SetHMenu(int hmenu);
		void SetHandler(HWND* hwndPtr);
		void SetTitle(text _title);
		operator long() { return TYPE.Id; }
	};
}
#endif

