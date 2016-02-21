#include "stdafx.h"
#include "InputMonitor.h"

#include "standbye_main.h" //Is needed here to prevent cross including

#define TO_MILLISECONDS(X) ((X) * 1000)

InputMonitor::InputMonitor(mainApplication^ parent, SettingsProvider* s) {
	aborted = false;
	this->parent = parent;
	settings_provider = s;
	Start();
}

InputMonitor::~InputMonitor()
{
	Stop();
	delete thread_start, watcher, settings_provider;
}

void InputMonitor::Monitor() {
	while (aborted == false) {
		if (SystemAccess::GetLastInputTime() == 0) {
			LOG("LastInputTime == 0 milliseconds");
		}

		if (SystemAccess::GetLastInputTime() > wait_time) {
			LOG("Wait Time is over!");
			parent->CheckUsage();
		}
		//Sleep only 10 milliseconds at once to handle to Close() Event
		for (int x = 0; x < wait_time; x = x + 10) {
			watcher->Sleep(10);
			if (aborted) {
				return;
			}
		}
	}
};

void InputMonitor::Reset() {
	Stop();
	Start();
}

void InputMonitor::Stop()
{
	aborted = true;
	watcher->Join();
	aborted = false;
}

void InputMonitor::Start() {
	wait_time = TO_MILLISECONDS(settings_provider->getThreshold(SettingName::WAIT_TIME));
	thread_start = gcnew ThreadStart(this, &InputMonitor::Monitor);
	watcher = gcnew Thread(thread_start);
	watcher->IsBackground = true;
	watcher->Name = "INPUT_MON";
	watcher->Start();
}