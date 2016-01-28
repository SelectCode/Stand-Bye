#pragma once
#include "stdafx.h"
#include "BasicFunc.h"
#include "SystemMetricWatcher.h"
#include "SystemAccess.h"

ref class InputMonitor {
private:
	void(*OnFinished)();
	int wait_time;
	bool aborted;
	ThreadStart^ thread_start;
	Thread^ watcher;
	SettingsProvider* settings_provider;

public:
	InputMonitor(SettingsProvider* s, void(*f)());
	~InputMonitor();

	void Reset();
	void Stop();
	void Start();

private:
	void Monitor();
};
