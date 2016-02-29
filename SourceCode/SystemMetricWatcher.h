//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: SystemMetricWatcher.h
 * Author: Matthias Weirich
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "SystemAccess.h"
#include "AverageBuffer.h"

using namespace System::Threading;

public ref class SystemMetricWatcher {
public:
	SystemMetricWatcher(SystemAccess^ system_access, int frequenzy, int time);
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
