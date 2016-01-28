#pragma once
//#include <afxwin.h>
#include <windows.h>
#define TRAY_ICON_MSG (WM_USER + 1)
#ifndef DEBUG
#define DEBUG(s) System::Diagnostics::Debug::WriteLine(s);
#define APPLICATION_NAME "Stand-Bye!"
#endif // !DEBUG(s)
