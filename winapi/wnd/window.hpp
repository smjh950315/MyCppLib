#pragma once
#ifndef CYH_WINDOW_H
#define CYH_WINDOW_H
#endif // !CYH_WINDOW_H
#include "../header.hpp"
#include "wndobj.hpp"
#define WND_DROPDOWN_LIST 10
#define WND_TYPE_INPUT 100
#define WND_TYPE_INPUT_MULTILINE 101
#define WND_TYPE_BUTTON 200
#define WND_TYPE_DISPLAY_REGION 300
using namespace cyh::winapi;
using cyh::winapi::wnd::BaseObj;
namespace cyh::winapi::wnd {
	struct WndSize {
		int Width, Height;
		WndSize();
		WndSize(int w, int h);
		void ReadSize(LPARAM lParam);
	};
	class WndClass : public WNDCLASSEX {
	public:
		WndClass();
		WndClass(HINSTANCE _hInstance, LRESULT(*WndProc)(HWND, UINT, WPARAM, LPARAM));
	};
	class WndApi;
	class Window {
	protected:		
		LRESULT BasicWndMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void _ptr_initiate();
		void _wnd_register();
		void _hWnd_register();
		void _setWndHandler();
		void _setWndHandler(HWND* hptr);
		void _load_object();
		void _add_option_to_dropdown_list(HWND* hCbBox,vector<text>& options);
		void _obj_create(BaseObj* obj);
	public:		
		int* nCmdShow = nullptr;
		HINSTANCE* hInstance = nullptr;
		WndClass* WndcPtr;
		HWND hWnd = 0;
		bool WndReg = false;
		bool HWndReg = false;	
		bool IsInitialized = false;
		bool DisableResize = false;		
		text WndCName = L"defaultClass";
		text WndTitle = L"";
		WndSize Size;
		vector<BaseObj*> Objects;
		WndObjType objType;
		LRESULT(*WndProcPtr)(HWND, UINT, WPARAM, LPARAM) = nullptr;
		HFONT hFont=NULL;
		Window();
		Window(HINSTANCE* _hInstance, int* _nCmdShow);
		~Window(){}
		void Configuration(int w, int h, text wndClass, text title);
		void SetHandlers(HINSTANCE* _hInstance, int* _nCmdShow);
		void SetWndProcess(LRESULT(*WndProc)(HWND, UINT, WPARAM, LPARAM));
		void Build();
		void AddObject(BaseObj* pObj);
	};

}