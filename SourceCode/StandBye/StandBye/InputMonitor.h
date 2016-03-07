//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: InputMonitor.h
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "SystemMetricWatcher.h"
#include "SystemAccess.h"

ref class mainApplication;

public  ref class InputMonitor {
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
