#include "stdafx.h"
#include "SystemMetricWatcher.h"

SystemMetricWatcher::SystemMetricWatcher(SettingsProvider* prov, int frequenzy, int time) {
	ThreadStart^ start = gcnew ThreadStart(this, &SystemMetricWatcher::Loop);
	background_thread = gcnew Thread(start);
	background_thread->IsBackground = true;

	this->frequenzy = frequenzy;

	int size = frequenzy*time;
	ram_buffer = gcnew AverageBuffer(size);
	cpu_buffer = gcnew AverageBuffer(size);
	hdd_buffer = gcnew AverageBuffer(size);
	network_buffer = gcnew AverageBuffer(size);

	system_access = gcnew SystemAccess(prov);
}

SystemMetricWatcher::~SystemMetricWatcher() {
	background_thread->Abort();
}

void SystemMetricWatcher::Start() {
	background_thread->Start();
}

void SystemMetricWatcher::Stop() {
	background_thread->Abort();
}

void SystemMetricWatcher::Loop() {
	while (true) {
		Sleep(float(1000.0f / frequenzy));
		ReadValues();
	}
}

float SystemMetricWatcher::GetSystemMetric(SystemAccess::SystemMetric s) {
	switch (s) {
	case SystemAccess::SystemMetric::CPU:
		return cpu_buffer->GetAverage();
	case SystemAccess::SystemMetric::HDD:
		return hdd_buffer->GetAverage();
	case SystemAccess::SystemMetric::RAM:
		return ram_buffer->GetAverage();
	case SystemAccess::SystemMetric::NETWORK:
		return network_buffer->GetAverage();
	default:
		return 0.0f;
	}
}

void SystemMetricWatcher::ReadValues() {
	cpu_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::CPU));

	ram_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::RAM));

	hdd_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::HDD));

	network_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::NETWORK));
}