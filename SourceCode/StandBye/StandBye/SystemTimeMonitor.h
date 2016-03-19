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
#include "SettingsProvider.h"

ref class mainApplication;

using System::Threading::Thread;
using System::Threading::ThreadStart;

ref class SystemTimeMonitor
{
private:
	mainApplication^ parent;
	SettingsProvider* settings_provider;
	System::Windows::Forms::Timer^ monTimer;
	DateTime standbyTime;
private:
	void OnTick(System::Object ^sender, System::EventArgs ^e);
public:
	SystemTimeMonitor(mainApplication^ sender, SettingsProvider* setProv);
	~SystemTimeMonitor()
	{
		delete monTimer;
	}
	void Stop();
};
