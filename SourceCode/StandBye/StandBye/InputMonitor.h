//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
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
	mainApplication^ parent;
	System::Windows::Forms::Timer^ monTimer;
	SettingsProvider* settings_provider;

public:
	InputMonitor(mainApplication^ parent, SettingsProvider* s);
	~InputMonitor();
	void Stop();

private:
	void Monitor(System::Object ^sender, System::EventArgs ^e);
};
