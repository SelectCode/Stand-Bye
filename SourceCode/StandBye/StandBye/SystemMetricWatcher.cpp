//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Matthias Weirich
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SystemMetricWatcher.h"

SystemMetricWatcher::SystemMetricWatcher(SystemAccess^ system_access, int frequency, int stored_samples) {
	//Variables
	this->system_access = system_access;

	//Initialize Buffers
	ram_buffer = gcnew AverageBuffer(stored_samples);
	cpu_buffer = gcnew AverageBuffer(stored_samples);
	hdd_buffer = gcnew AverageBuffer(stored_samples);
	network_buffer = gcnew AverageBuffer(stored_samples);
	sound_buffer = gcnew AverageBuffer(stored_samples);

	//Starts Timer
	monTimer = gcnew System::Windows::Forms::Timer();
	monTimer->Interval = 1000 / frequency;
	monTimer->Tick += gcnew System::EventHandler(this, &SystemMetricWatcher::ReadValues);
	monTimer->Start();
}

SystemMetricWatcher::~SystemMetricWatcher() {
	monTimer->Stop();
	delete monTimer;
	delete cpu_buffer;
	delete ram_buffer;
	delete hdd_buffer;
	delete network_buffer;
	LOG("System Metric Watcher destroyed");
}

void SystemMetricWatcher::Stop() {
	monTimer->Stop();
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
	case SystemAccess::SystemMetric::SOUND:
		return sound_buffer->GetAverage();
	default:
		return 0.0f;
	}
}

void SystemMetricWatcher::ReadValues(System::Object^, System::EventArgs^) {
	//reads all system metric usages
	cpu_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::CPU));
	ram_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::RAM));
	hdd_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::HDD));
	network_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::NETWORK));
	sound_buffer->Put(system_access->GetMetric(SystemAccess::SystemMetric::SOUND));
}