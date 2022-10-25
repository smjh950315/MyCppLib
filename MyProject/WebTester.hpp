#pragma once
#ifndef WEB_TESTER_H
#define WEB_TESTER_H
#include "../winapi/winapi.hpp"
#include "../web/web.hpp"
#include "../time/time.hpp"
#include "../data/json.hpp"
using namespace cyh::graph;
using namespace cyh::Time;
using namespace cyh::data;
using namespace cyh::winapi;
using namespace cyh::winapi::wnd;
namespace cyh::myproject::tester {

#define IDB_EXIT 1000
#define IDB_ADD_INPUT 101
#define IDB_SUBMIT 201
#define IDB_RESPONSE_RESULT 301
#define IDB_FUNC_DROPDOWN 501
#define IDB_URL_IN 2000
#define IDB_JSON_IN 3000
	using api = WndApi;
	static int WndW = 800;
	static int WndH = 600;
	static TCHAR PClassName[] = L"CyhTester";
	static TCHAR PTitleName[] = L"Web Tester";

	static text msgbox_title(' ', 256);
	static text input_buffer(' ', 256);
	static text json_input_buffer(' ', 10000);
	static text response_buffer(' ', 10000);

	static HWND hModeBtn;
	static HWND hSubmitBtn;
	static HWND hUrlInput;
	static bool UrlInShow;
	static HWND hContextOutput;
	static HWND hContextInput;


	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static class WebTester : public Window {
	private:
	public:

		ObjSize sbb = ObjSize(100, 30);
		ObjSize stbUrl = ObjSize(300,60);
		ObjSize stbb = ObjSize(300, 400);
		HFONT default_font = api::BasicFont(16);

		Button* BtnChangeMode = new Button(sbb, 600, 10, "HIDE/SHOW", &hModeBtn, IDB_ADD_INPUT);
		Button* BtnSubmit = new Button(sbb, 380, 10, "Submit", &hSubmitBtn, IDB_SUBMIT);
		TextBox* UrlIn = new TextBox(stbUrl,60,10,&hUrlInput,IDB_URL_IN);
		TextBox* ContextIn = new TextBox(stbb, 60, 100, &hContextInput, IDB_JSON_IN);
		TextDisplay* ContextDp = new TextDisplay(stbb, 380, 100, &hContextOutput, IDB_RESPONSE_RESULT);

		WebTester(HINSTANCE* _hInstance, int* _nCmdShow) {
			Configuration(WndW, WndH, PClassName, PTitleName);
			SetHandlers(_hInstance, _nCmdShow);
			SetWndProcess(WndProc);
			Initialization();
		}

		void Initialization() {
			DisableResize = true;
			AddObject(BtnChangeMode);
			AddObject(BtnSubmit);
			AddObject(UrlIn);
			AddObject(ContextDp);
			AddObject(ContextIn);
		}
		void PostJson(HWND hWnd, text _url, text& _json, text& _buffer) {
			msgbox_title = "Success!  ";
			Timer t;
			cyh::web::CurlClient::HttpPost(_url, _json, _buffer, t);
			msgbox_title += t.DMilliStr();
			Json js;
			js.ReadFromText(_buffer);
			_buffer = js.ToTextByStructForWinApi();
			api::SetText(ContextDp, ContextDp->Text);
		}
	};
	static WebTester* WTptr;
	static void GetInstancePointer(WebTester* wt) {
		if (!WTptr) {
			WTptr = wt;
		}
	}
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		LRESULT result = 0;
		PAINTSTRUCT ps;
		HDC hdc;
		switch (message)
		{
		case WM_CREATE:

			break;
		case WM_INITDIALOG:

			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDB_EXIT:
				PostQuitMessage(0);
				break;
			case IDB_ADD_INPUT:
				if (UrlInShow) {
					api::HideItem(hUrlInput);
					UrlInShow = false;
				}
				else {
					api::ShowItem(hUrlInput);
					UrlInShow = true;
				}
				break;
			case IDB_SUBMIT:
				api::GetText(WTptr->UrlIn);
				api::GetText(WTptr->ContextIn);
				WTptr->PostJson(hWnd, WTptr->UrlIn->Text, WTptr->ContextIn->Text, WTptr->ContextDp->Text);				
				api::ShowMsgBox(hWnd, "rqTime", msgbox_title);
				break;
			default:
				break;
			}
		case WM_DISPLAYCHANGE:
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			api::ShowText(hdc, 20, 20, "Url:");
			api::SetItemFont(WTptr->UrlIn, WTptr->default_font);
			api::SetItemFont(WTptr->ContextIn, WTptr->default_font);
			api::SetItemFont(WTptr->ContextDp, WTptr->default_font);
			EndPaint(hWnd, &ps);
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
}

#endif // !WEB_TESTER_H
