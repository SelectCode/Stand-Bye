//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader, Stephan Le
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SettingsProvider.h"
#include <string>
#include <vector>
#include <iostream>
#include <Psapi.h> //To get Processes
#include <stdio.h>//To get Processes
#include <tchar.h>//To get Processes
#include <lmcons.h> //To get user name
#include <WtsApi32.h>

using namespace System::Diagnostics;
using namespace System::Collections::Generic;
using System::Windows::Forms::Timer;
using System::Windows::Forms::Application;
using System::Windows::Forms::PowerState;
struct IAudioMeterInformation; //To avoid cross linking

public ref class SystemAccess {
private:
	//Attributes
	PerformanceCounter^ perfCPU;
	PerformanceCounter^ perfHDD;
	List<PerformanceCounter^>^ perfNETs;
	SettingsProvider* setprov;

	//Methods
	float getCPUUsage();
	float getRAMUsage();
	float getNETUsage();
	float getHDDUsage();

public:
	SystemAccess(SettingsProvider* p);
	~SystemAccess();

	enum class  SystemMetric : char { CPU, RAM, NETWORK, HDD, SOUND };

	float GetMetric(SystemMetric s);

	static void StartESM();

	static std::vector<std::string> GetNetAdapterNames();

	static float GetLastInputTime();

	static std::vector<std::string> GetRunningProccesses();

	static void SetPresentationMode(boolean value);

	static void SetAutoStart(boolean value);

	static void EnableWindowsStandBy();

	static void DisableWindowsStandBy();

	static bool isUserActive();

	static bool IsInAutoStart();

	static float getAudioPeak();

	static List<String^>^ getLoggedInUsers();

	static String^ getActiveUser();

	static String^ getStartUserOfStandbye();

	static bool MultiUsersPreventStandby();

	static String^ getStandByeFolderPath();
};
