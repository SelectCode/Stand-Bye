#include "stdafx.h"
#include "InputMonitor.h"

#define TO_MILLISECONDS(X) ((X) * 1000)

InputMonitor::InputMonitor(SettingsProvider* s, void(*f)()) {
	aborted = false;
	OnFinished = f;
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
			DEBUG("LastInputTime == 0 milliseconds");
		}

		if (SystemAccess::GetLastInputTime() > wait_time) {
			DEBUG("Wait Time is over!");
			OnFinished();
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