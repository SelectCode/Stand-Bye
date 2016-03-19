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

using System::String;
using namespace System::Threading;
using System::Windows::Forms::Timer;

ref class mainApplication;
ref class InstanceMonitor
{
private:
	mainApplication^ mApplication;
	System::Windows::Forms::Timer^ monTimer;
	HANDLE hMutex;
	bool anotherInstanceRunning;
	bool exit = false;
	String^ path;
	void monitor(System::Object^, System::EventArgs^);
	void writeFile();
	void deleteFile();

public:
	InstanceMonitor(mainApplication^ parent);
	~InstanceMonitor()
	{
		delete monTimer;
	}
	bool isAnotherInstanceRunning();
	void Destroy();
};
