#pragma once
#ifndef WIN_INCLUDE_H
#define WIN_INCLUDE_H
#include "../includeList.h"
#include "../data/text.hpp"
#include <commctrl.h>
#include <WinSock2.h>
#include <Windows.h>
#include <windowsx.h>
#include <windef.h>
#pragma comment (lib, "Ws2_32.lib")
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
#include <d2d1.h>
#pragma comment(lib, "d2d1")
using cyh::data::text;
namespace cyh::winapi {

}
#endif //!WIN_INCLUDE_H