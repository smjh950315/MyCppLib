#define _WINDOWS
#include "cyh.hpp"
#include "MyProject/testproj.hpp"
#include "MyProject/testproj.cpp"
using namespace cyh::Graph;
using namespace cyh::MultiThread;
using namespace cyh::Time;
using namespace cyh::winapi;
using namespace cyh::winapi::wnd;
using namespace cyh::myproject::testproj;
//int main()
//{
//	system("pause");
//}


ImgTest* WndPtr;
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{

	WndConfig cfg = WndConfig(500, 400, "WndClassName", L"¥Ë«Î");
	ImgTest Wnd(&hInstance, &nCmdShow, cfg);
	Wnd.Initiate();
	Wnd.Build();

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//system("pause");
}
