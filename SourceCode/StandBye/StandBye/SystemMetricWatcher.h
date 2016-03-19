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
#pragma once
#include "stdafx.h"
#include "SystemAccess.h"
#include "AverageBuffer.h"

public ref class SystemMetricWatcher {
private:
	SystemAccess^ system_access;
	System::Windows::Forms::Timer^ monTimer;
	AverageBuffer^ cpu_buffer, ^network_buffer, ^hdd_buffer, ^ram_buffer, ^sound_buffer;
	void ReadValues(System::Object^, System::EventArgs^);

public:
	SystemMetricWatcher(SystemAccess^ system_access, int frequenzy, int time);
	~SystemMetricWatcher();
	void Stop();
	float GetSystemMetric(SystemAccess::SystemMetric s);
};
