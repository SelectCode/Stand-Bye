#pragma once
#include "SettingsProvider.h"
#include <string>
#include <vector>
#include <iostream>
#include <Psapi.h> //To get Processes
#include <stdio.h>//To get Processes
#include <tchar.h>//To get Processes

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

	static bool IsInAutoStart();

	static float getAudioPeak();
};
