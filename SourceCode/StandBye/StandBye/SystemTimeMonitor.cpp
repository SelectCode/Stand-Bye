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

#include "SystemTimeMonitor.h"
#include "mainApplication.h"

SystemTimeMonitor::SystemTimeMonitor(mainApplication^ sender, SettingsProvider* setProv)
{
	parent = sender;
	settings_provider = setProv;
	monTimer = gcnew System::Windows::Forms::Timer();
	monTimer->Interval = 1000;
	monTimer->Tick += gcnew System::EventHandler(this, &SystemTimeMonitor::OnTick);
}

void SystemTimeMonitor::Stop()
{
	//Stops Thread
	monTimer->Stop();
}

void SystemTimeMonitor::OnTick(System::Object ^, System::EventArgs ^)
{
	if ((DateTime::Now.Hour == standbyTime.Hour) && (DateTime::Now.Minute == standbyTime.Minute)) {
		monTimer->Stop();
		parent->checkSystemAndStandby();
		monTimer->Start();
	}
}