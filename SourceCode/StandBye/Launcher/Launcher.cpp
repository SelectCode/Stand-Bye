// Launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Launcher.h"
#include <string>
#include <iostream>

#define COMMAND _T("PORTABLE")
#define RELPATH "\\bin\\StandBye.exe"

LPCWSTR toL(std::string s) {
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	return sw;
}

std::string getExePath() {
	wchar_t result[MAX_PATH];
	GetModuleFileName(NULL, result, MAX_PATH);
	std::wstring ws(result);

	std::string moduleFileName(ws.begin(), ws.end() );

	std::string baseDir = moduleFileName.substr(0, moduleFileName.find_last_of("\\/"));

	std::string exePath = baseDir + RELPATH;

	return exePath;

}

std::string getCommand() {}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow) {

	OutputDebugString(toL(getExePath() + "\n"));

	/**
	PROCESS_INFORMATION ProcessInfo; //
	STARTUPINFO StartupInfo; //Unused, but necessary for createprocess

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field


	if(CreateProcess(getExePaht(),COMMAND,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo)) {
	} else {
		
	}*/

	return 0;
}

