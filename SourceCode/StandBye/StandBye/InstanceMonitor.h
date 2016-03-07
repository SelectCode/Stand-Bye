//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: InstanceMonitor.h
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"

using System::String;
using namespace System::Threading;

ref class mainApplication;
ref class InstanceMonitor
{
private:
	mainApplication^ mApplication;
	Thread^ monThread;
	HANDLE hMutex;
	bool anotherInstanceRunning;
	bool exit = false;
	String^ path;
	void monitor();
	void writeFile();
	void deleteFile();

public:
	InstanceMonitor(mainApplication^ parent);
	bool isAnotherInstanceRunning();
	void Destroy();
};
