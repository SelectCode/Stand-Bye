//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: InstanceMonitor.cpp
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "InstanceMonitor.h"
#include "standbye_main.h"
//#define WM_REQUEST_OPEN_SETTINGS (WM_USER+1)
#define FILENAME "standBye.tmp"
using namespace System::Diagnostics;
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
		monThread = gcnew Thread(gcnew ThreadStart(this, &InstanceMonitor::monitor));
		monThread->IsBackground = true;
		monThread->Priority = ThreadPriority::Normal;
		monThread->Name = "INST_MON";
		monThread->Start();
	}
	else {
		LOG("Another Instance of Stand-Bye! is running!");
		LOG("Exiting...");
		anotherInstanceRunning = true;
		writeFile();
	}
}

void InstanceMonitor::monitor()
{
	while (exit == false) {
		if (!File::Exists(path)) {
			System::Threading::Thread::Sleep(50);
		}
		else {
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
	exit = true;
	monThread->Join();
	deleteFile();
	LOG("Detroyed Instance Monitor!");
}