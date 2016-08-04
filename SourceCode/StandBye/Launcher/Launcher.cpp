// Launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Launcher.h"
#include <string>
#include <vector>
#include <strsafe.h>

#pragma comment(lib,"user32.lib") 

#define RELPATH std::wstring(L"\\bin\\StandBye.exe")

std::wstring getExePath() {

	//Get the path to the currently running exe
	wchar_t result[MAX_PATH]; //buffer, used as [out] variable
	GetModuleFileName(NULL, result, MAX_PATH);// returns path to currently running exe

	//convert buffer to wstring
	std::wstring moduleFileName(result);

	//remove file name
	std::wstring baseDir = moduleFileName.substr(0, moduleFileName.find_last_of(L"\\/"));

	//append relative path to StandBye exe
	std::wstring exePath = baseDir + RELPATH;

	return exePath;

}

int showErrorMessage() {

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf)  + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT(" StandBye! could not be launched. Error %d: %s"), dw, lpMsgBuf);
	int clicked = MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_RETRYCANCEL | MB_ICONEXCLAMATION | MB_SETFOREGROUND);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);

	return clicked;
	
}

void tryToLaunch(std::wstring path) {

	if(!launchMainExe(path)) {

		int clicked = showErrorMessage();

		if(clicked == IDRETRY) {
			tryToLaunch(path);
		} else if(clicked == IDCANCEL) {
			ExitProcess(-1);
		}

	}

}

//launches the exe at the specified location
BOOL launchMainExe(std::wstring string) {

	//Convert path to LPWSTR
	std::vector<wchar_t> vec(string.begin(), string.end());
	vec.push_back(L'\0');
	LPWSTR path = &vec[0];


	PROCESS_INFORMATION ProcessInfo; // unused, but necesarry for createprocess
	STARTUPINFO si; //Unused, but necessary for createprocess
	ZeroMemory(&si, sizeof(si)); //init memory
	si.cb = sizeof si; //Only compulsory field

	wchar_t command[] = L"-PORTABLE"; //Must be editable, cannot be a literal

	return CreateProcessW(path, //path to executable
		command, //cmd params
		NULL, NULL, FALSE, 0, NULL, NULL,
		&si,// in param on how to create the process
		&ProcessInfo // out param, info on created process
	);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow) {

	tryToLaunch(getExePath());

	return 0;
}

