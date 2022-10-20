#pragma once
#ifndef CYH_WND_OBJ_TYPE_H
#define CYH_WND_OBJ_TYPE_H
#include "../header.hpp"
namespace cyh::winapi::wnd {
	struct ObjType {
		long Id = 0;
		const wchar_t* lpClassName = nullptr;
		long dwStyle = WS_VISIBLE | WS_CHILD;
		ObjType() {}
		ObjType(long id, const wchar_t* lpCN, long dwS)
		{
			Id = id, lpClassName = lpCN, dwStyle = dwS;
		}
		operator long() { return Id; }
	};
	//====================================
	/*
		Roles:
			1XXX: Input
				11XX: Text
				12XX: Button

			2XXX: Output
				21XX: Text

			3XXX: COMBO BOX TYPES
				31XX: DropDowmList
	*/
	//====================================
	static class WndObjType {
	public:
		ObjType SingleLineTextInput = ObjType(
			1100,
			L"EDIT",
			WS_VISIBLE | WS_CHILD | WS_BORDER
		);
		ObjType MultiLineTextInput = ObjType(
			1101,
			L"EDIT",
			WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
			ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN
		);
		ObjType Button = ObjType(
			1200,
			L"BUTTON",
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON
		);
		ObjType MultiLineDisplayRegion = ObjType(
			2100,
			L"EDIT",
			WS_VISIBLE | WS_CHILD | ES_READONLY |
			ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN |
			WS_VSCROLL | WS_BORDER
		);
		ObjType DropDownList = ObjType(
			3100,
			L"COMBOBOX",
			WS_VISIBLE | CBS_DROPDOWN | CBS_HASSTRINGS |
			WS_CHILD | WS_OVERLAPPED
		);
	};
}

#endif