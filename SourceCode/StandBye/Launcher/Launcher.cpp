// Launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Launcher.h"
#include <string>
#include <vector>

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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow) {

	//Get exe path
	std::wstring string = getExePath();

	//Convert path to LPWSTR
	std::vector<wchar_t> vec(string.begin(), string.end());
	vec.push_back(L'\0');
	LPWSTR path = &vec[0];


	PROCESS_INFORMATION ProcessInfo; // unused, but necesarry for createprocess
	STARTUPINFO si; //Unused, but necessary for createprocess
	ZeroMemory(&si, sizeof(si)); //init memory
	si.cb = sizeof si; //Only compulsory field

	wchar_t command[] = L"-PORTABLE"; //Must be editable, cannot be literal

	if(CreateProcessW(path, //path to executable
		command, //cmd params
		NULL, NULL, FALSE, 0, NULL, NULL,
		&si,// in param on how to create the process
		&ProcessInfo // out param, info on created process
		)) {
		//TODO: Proper error handling
	} else {

	}

	return 0;
}

