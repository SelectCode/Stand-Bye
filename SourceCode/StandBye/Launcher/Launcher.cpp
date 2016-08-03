// Launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Launcher.h"
#include <string>
#include <vector>

#define RELPATH std::wstring(L"\\bin\\StandBye.exe")
#define LOG_D(x) OutputDebugString(x)

LPCWSTR toL(std::string s) {
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	return sw;
}

std::wstring getExePath() {
	wchar_t result[MAX_PATH];
	GetModuleFileName(NULL, result, MAX_PATH);
	std::wstring moduleFileName(result);

	std::wstring baseDir = moduleFileName.substr(0, moduleFileName.find_last_of(L"\\/"));

	std::wstring exePath = baseDir + RELPATH;

	return exePath;

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow) {

    //Get exe path
	std::wstring string = getExePath();

	//Convert to LPWSTR
	std::vector<wchar_t> vec(string.begin(), string.end());
	vec.push_back(L'\0');
	LPWSTR path = &vec[0];

	LOG_D(path);
	LOG_D(L"\n");

	PROCESS_INFORMATION ProcessInfo; //
	STARTUPINFO si; //Unused, but necessary for createprocess


	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof si; //Only compulsory field

	wchar_t command[] = L"-PORTABLE"; //Must be editable, cannot be literal

	if(CreateProcessW(path, //path to executable
		command, //cmd params
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,// in param on how to create the process
		&ProcessInfo // out param, info on created process
		)) {
		LOG_D(_T("process created\n"));
	} else {
		LOG_D(_T("process not created\n"));
		//LOG_D((LPCWSTR(GetLastError())));
	}

	return 0;
}

