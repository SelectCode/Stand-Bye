#pragma once
#include "stdafx.h"
#include "BasicFunc.h"
#include "SystemMetricWatcher.h"
#include "SystemAccess.h"

ref class mainApplication;

ref class InputMonitor {
private:
	int wait_time;
	bool aborted;
	mainApplication^ parent;
	ThreadStart^ thread_start;
	Thread^ watcher;
	SettingsProvider* settings_provider;

public:
	InputMonitor(mainApplication^ parent, SettingsProvider* s);
	~InputMonitor();

	void Reset();
	void Stop();
	void Start();

private:
	void Monitor();
};
