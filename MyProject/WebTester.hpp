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

	using api = WndApi;
	static int WndW = 800;
	static int WndH = 600;
	static TCHAR PClassName[] = L"CyhTester";
	static TCHAR PTitleName[] = L"Web Tester";
	static HWND hUrlInput;
	static bool UrlInShow;
	static HWND hContextOutput;
	static HWND hContextInput;
	static text msgbox_title(' ', 256);
	static text input_buffer(' ', 256);
	static text json_input_buffer(' ', 10000);
	static text response_buffer(' ', 10000);		

	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static class WebTester : public Window {
	private:
	public:
		//CurlClient curlClient;
		WebTester(HINSTANCE* _hInstance, int* _nCmdShow) {
			Configuration(WndW, WndH, PClassName, PTitleName);
			SetHandlers(_hInstance, _nCmdShow);
			SetWndProcess(WndProc);
			Initialization();
		}
		void Initialization() {
			DisableResize = true;
			AddButton(600, 20, 100, 30, L"HIDE/SHOW", IDB_ADD_INPUT);
			AddInputBoxMultiLine(60, 10, 300, 60, &hUrlInput);
			AddButton(380, 10, 100, 60, L"Submit", IDB_SUBMIT);
			AddInputBoxMultiLine(60, 100, 300, 400, &hContextInput);
			AddDisplayRegin(380, 100, 300, 400, IDB_RESPONSE_RESULT);
		}
		void PostJson(HWND hWnd, text _url, text& _json, text& _buffer) {
			msgbox_title = "Success!  ";
			Timer t;
			//cyh::web::CurlClient::HttpPost(_url, _json, _buffer, t);
			cyh::web::CurlClient::HttpGet(_url, _buffer, t);
			msgbox_title += t.DMilliStr();
			Json js;
			js.ReadFromText(_buffer);
			_buffer = js.ToTextByStructForWinApi();
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
				api::GetInputText(hUrlInput, input_buffer, 256);
				api::GetInputText(hContextInput, json_input_buffer, 1000);
				WTptr->PostJson(hWnd, input_buffer, json_input_buffer, response_buffer);
				api::SetText(hWnd, response_buffer, IDB_RESPONSE_RESULT);
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
