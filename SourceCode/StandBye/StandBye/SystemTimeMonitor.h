#pragma once
#include "stdafx.h"
#include "SettingsProvider.h"

ref class mainApplication;

using System::Threading::Thread;
using System::Threading::ThreadStart;

ref class SystemTimeMonitor
{
private:
	mainApplication^ parent;
	SettingsProvider* settings_provider;
	Thread^ MonThread;
	DateTime standbyTime;
	bool exit = false;

private:
	void MonitorTime();
public:
	SystemTimeMonitor(mainApplication^ sender, SettingsProvider* setProv);
	void Start();
	void Reset();
	void Stop();
};
