//#define _WINDOWS
#include "cyh.hpp"
#include "web/curlclient.hpp"
//#include "MyProject/WebTester.hpp"
using namespace cyh::graph;
using namespace cyh::MultiThread;
using namespace cyh::Time;
using namespace cyh::web;
using namespace cyh::data;
using namespace cyh::cfilesystem;
//using namespace cyh::winapi;
//using namespace cyh::winapi::wnd;
//using namespace cyh::myproject;
//using namespace cyh::myproject::tester;

int main() {
	string in = "ABCD";
	std::reverse(in.begin(), in.end());
	cout << in << endl;
	system("pause");
}

//int WINAPI WinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow)
//{
//
//	WebTester Wnd(&hInstance, &nCmdShow);
//	GetInstancePointer(&Wnd);
//	Wnd.Build();
//	//system("pause");
//}


