//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "InstanceMonitor.h"
#include "mainApplication.h"
//#define WM_REQUEST_OPEN_SETTINGS (WM_USER+1)
#define FILENAME "standBye.tmp"
using namespace System::IO;

InstanceMonitor::InstanceMonitor(mainApplication ^ parent)
{
	TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
	path = Path::Combine(gcnew String(buf), FILENAME);

	mApplication = parent;
	//Checks if another instance is running
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, "Stand-Bye");
	LOG("Instance Monitor trys to open Mutex!");

	if (!hMutex) {
		//Mutex does not exist --> first instance
		hMutex = CreateMutex(0, 0, "Stand-Bye");
		anotherInstanceRunning = false;
		LOG("Instance Monitor: No other instance running");

		//Deletes File --> is first instance
		deleteFile();

		//Starts monitor Thread
		monTimer = gcnew System::Windows::Forms::Timer();
		monTimer->Tick += gcnew System::EventHandler(this, &InstanceMonitor::monitor);
		monTimer->Interval = 1000;
		monTimer->Start();
	}
	else {
		LOG("Another Instance of Stand-Bye! is running!");
		LOG("Exiting...");
		anotherInstanceRunning = true;
		writeFile();
	}
}

void InstanceMonitor::monitor(System::Object^, System::EventArgs^)
{
	if (File::Exists(path)) {
		try {
			mApplication->OpenSettingsForm();
			LOG("TEMP File existed --> Opend Settingsform");
		}
		catch (Exception^ e) {
			LOG("Could not open Settingsform!");
			LOG(e->Message);
		}
		deleteFile();
	}
}
void InstanceMonitor::writeFile()
{
	String^ text = "Please ignore this file.";
	File::WriteAllText(path, text);
	LOG("Written TEMP File: " + BasicFunc::StringToString(path));
}

void InstanceMonitor::deleteFile()
{
	if (File::Exists(path)) {
		File::Delete(path);
		LOG("Deleted TEMP file: " + BasicFunc::StringToString(path));
	}
	else {
		LOG("Deleted TMP File [not existed]");
	}
}

bool InstanceMonitor::isAnotherInstanceRunning()
{
	return anotherInstanceRunning;
}

void InstanceMonitor::Destroy()
{
	ReleaseMutex(hMutex);
	monTimer->Stop();
	deleteFile();
	LOG("Detroyed Instance Monitor!");
}