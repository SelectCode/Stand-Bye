#pragma once
#include "SettingsProvider.h"
#include "BasicFunc.h"
#include <string>
#include <vector>
#include <iostream>
#include <Psapi.h> //To get Processes
#include <stdio.h>//To get Processes
#include <tchar.h>//To get Processes

using System::Windows::Forms::Timer;
using System::Windows::Forms::Application;
using System::Windows::Forms::PowerState;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

public ref class SystemAccess {
private:
	PerformanceCounter^ perfCPU;
	PerformanceCounter^ perfHDD;
	List<PerformanceCounter^>^ perfNETs;

	SettingsProvider* setprov;
	float getCpuUsage();
	float getRamUsage();
	float getNetworkUsage();
	float getHddUsage();

public:
	SystemAccess(SettingsProvider* p);
	~SystemAccess();

	enum class  SystemMetric : char { CPU, RAM, NETWORK, HDD };

	float GetMetric(SystemMetric s);

	static void StartESM();

	static std::vector<std::string> GetNetAdapterNames();

	static float GetLastInputTime();

	static std::vector<std::string> GetRunningProccesses();

	static void SetPresentationMode(boolean value);

	static void SetAutoStart(boolean value);

	static boolean IsInAutoStart();
};
