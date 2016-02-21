#pragma once
#include "stdafx.h"
#include "SystemAccess.h"
#include "AverageBuffer.h"

using namespace System::Threading;

public ref class SystemMetricWatcher {
public:
	SystemMetricWatcher(SettingsProvider* settings_provider_, int frequenzy, int time);
	~SystemMetricWatcher();
	void Start();
	void Stop();
	void Loop();
	float GetSystemMetric(SystemAccess::SystemMetric s);

private:
	Thread^ background_thread;
	AverageBuffer^ cpu_buffer, ^network_buffer, ^hdd_buffer, ^ram_buffer, ^sound_buffer;
	SystemAccess^ system_access;
	void ReadValues();
	int frequenzy;
};
