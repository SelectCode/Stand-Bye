#pragma once
//#include <afxwin.h>
#include <windows.h>
#include "BasicFunc.h"
#define TRAY_ICON_MSG (WM_USER + 1)
#ifndef LOG
#define LOG(s) BasicFunc::Log(s)
#define APPLICATION_NAME "Stand-Bye!"
#endif // !DEBUG(s)
