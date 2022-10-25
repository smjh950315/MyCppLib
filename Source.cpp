#include "cyh.hpp"
using cyh::data::text;
using cyh::math::Polynomial;
using namespace cyh::cfilesystem;
int main() {

	Polynomial p("x");
	p = L"((¥Ò¥Ò+(b*d))+(c/d))";

	system("pause");
}
//#define _WINDOWS
//#include "web/curlclient.hpp"
//#include "MyProject/WebTester.hpp"
//using namespace cyh::myproject;
//using namespace cyh::myproject::tester;
//using namespace cyh::winapi;
//using namespace cyh::winapi::wnd;
//int WINAPI WinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	WebTester Wnd(&hInstance, &nCmdShow);
//	GetInstancePointer(&Wnd);
//	Wnd.Build();
//}


