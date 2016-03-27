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
#include "stdafx.h"
#include "InputMonitor.h"
#include "mainApplication.h" //Is needed here to prevent cross including

#define SECONDS_TO_MILLIS(x) x * 1000

InputMonitor::InputMonitor(mainApplication^ parent, SettingsProvider* s) {
	this->parent = parent;
	settings_provider = s;
	monTimer = gcnew System::Windows::Forms::Timer();
	monTimer->Tick += gcnew System::EventHandler(this, &InputMonitor::Monitor);
	monTimer->Interval = 500;
	monTimer->Start();
}

InputMonitor::~InputMonitor()
{
	Stop();
	delete monTimer;
}

void InputMonitor::Stop()
{
	monTimer->Stop();
}

void InputMonitor::Monitor(System::Object ^, System::EventArgs ^)
{
	if ((SECONDS_TO_MILLIS(settings_provider->getThreshold(SettingName::WAIT_TIME)) - SystemAccess::GetLastInputTime()) < SECONDS_TO_MILLIS(10)) {
		//Only 10 sec left
		parent->startMetricWatcher();
	}
	else {
		parent->stopMetricWatcher();
	}

	if (SystemAccess::GetLastInputTime() > settings_provider->getThreshold(SettingName::WAIT_TIME) * 1000) {
		LOG("Wait Time is over!");
		this->Stop();
		parent->checkSystemAndStandby();
		monTimer->Start();
	}
	
}