//#pragma once
//#define _WINDOWS
//#include "../cyh.hpp"
//using namespace cyh::graph;
//using namespace cyh::MultiThread;
//using namespace cyh::Time;
//using namespace cyh::winapi;
//using namespace cyh::winapi::wnd;
//
//#define IDB_EXIT 100
//#define IDB_SHOWMSG_BOX 101
//#define IDB_INPUT 102
//#define IDB_SHOW_IMG 103
//namespace cyh::myproject {
//	namespace testproj {
//		static HWND Input;
//		static text buffer(' ',100);
//		static cv::Mat mat;
//		static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//		static void ReadAndShow(text path);
//		class ImgTest : public Window {
//		public:			
//
//			ImgTest(HINSTANCE* _hInstance, int* _nCmdShow, WndConfig cfg) {
//				SetHandlers(_hInstance, _nCmdShow, cfg);
//				SetWndProcess(WndProc);
//			}
//			void Initiate() {
//				AddInputBox(10, 0, 150, 25, &Input);
//				AddButton(10, 50, 50, 50, "Exit", IDB_EXIT);
//				AddButton(10, 150, 150, 50, "ShowText", IDB_SHOWMSG_BOX);
//				AddButton(10, 250, 150, 50, "ShowImg", IDB_SHOW_IMG);
//			}
//			
//		};
//
//		static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//			PAINTSTRUCT ps;
//			HDC hdc;
//			switch (message)
//			{
//			case WM_COMMAND:
//				switch (LOWORD(wParam))
//				{
//				case IDB_EXIT:
//					PostQuitMessage(0);
//					break;
//				case IDB_SHOW_IMG:
//					GetWindowText(Input, buffer, 100);
//					ReadAndShow(buffer);
//					break;
//				case IDB_SHOWMSG_BOX:					
//					GetWindowText(Input, buffer, 100);
//					WndApi::ShowMsgBox(hWnd, "MsgBox Of Godch", buffer);
//					break;
//				default:
//					break;
//				}
//			case WM_PAINT:
//				hdc = BeginPaint(hWnd, &ps);
//				EndPaint(hWnd, &ps);
//				break;
//			case WM_DESTROY:
//				PostQuitMessage(0);
//				break;
//			default:
//				return DefWindowProc(hWnd, message, wParam, lParam);
//				break;
//			}
//			return 0;
//		}
//
//
//	}
//
//
//}