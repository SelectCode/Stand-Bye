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

	Microsoft::Win32::SystemEvents::PowerModeChanged += gcnew Microsoft::Win32::PowerModeChangedEventHandler(this, &InputMonitor::OnPowerModeChanged);

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

void InputMonitor::OnPowerModeChanged(Object ^ sender, PowerModeChangedEventArgs ^ e) {
	LOG("Power Mode Changed:");
	switch(e->Mode) {
	default:
		LOG("\tUnknown Change");
		break;
	case PowerModes::Resume:

		wakeTime = System::DateTime::Now;
		LOG("\tResuming System");

		break;
	case PowerModes::StatusChange:
		LOG("\tStatus Change");
		break;
	case PowerModes::Suspend:
		LOG("\tSuspending System");
		break;
	}
}

void InputMonitor::Monitor(System::Object ^, System::EventArgs ^)
{
	if ((SECONDS_TO_MILLIS(settings_provider->getThreshold(SettingName::WAIT_TIME)) - SystemAccess::GetLastInputTime()) < SECONDS_TO_MILLIS(10)) {
		//Only 10 sec left
		parent->startMetricWatcher();
	}
	else {
		parent->StopMetricWatcher();
	}

	if (SystemAccess::GetLastInputTime() > settings_provider->getThreshold(SettingName::WAIT_TIME) * 1000) {
		
		LOG("Wait Time is over!");
		
		System::DateTime now = System::DateTime::Now;
		TimeSpan t = now.Subtract(wakeTime);
		if(t.TotalMinutes > 1) {
			LOG("Protection time is over");
			this->Stop();
			parent->checkSystemAndStandby(true);
			monTimer->Start();
		} else {
			LOG("Protection time is not over yet");
		}
	}
}