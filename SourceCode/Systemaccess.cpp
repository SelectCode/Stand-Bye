#include "stdafx.h"
#include "SystemAccess.h"

float SystemAccess::getCpuUsage() {
	//Note: performance counters need administrator privileges at Windows Vista
	float cpuUsage_percent = perfCPU->NextValue();
	return cpuUsage_percent;
}

float SystemAccess::getRamUsage()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	ULONGLONG totalPhysMem = memInfo.ullTotalPhys;
	ULONGLONG usedPhysMem = totalPhysMem - memInfo.ullAvailPhys;
	return (float)(100.0 * usedPhysMem / totalPhysMem);
}

float SystemAccess::getNetworkUsage() {
	float kbytes_per_sec = 0;
	for each(PerformanceCounter^ perf in *perfNETs) {
		kbytes_per_sec += perf->NextValue() / 1000;
	}
	return kbytes_per_sec;
}

float SystemAccess::getHddUsage()
{
	float kbytes_per_sec = perfHDD->NextValue() / 1000;
	return kbytes_per_sec;
}

SystemAccess::SystemAccess(SettingsProvider* p)
{
	setprov = p;
	perfCPU = gcnew PerformanceCounter("Processor", "% Processor Time", "_Total");
	perfHDD = gcnew PerformanceCounter("PhysicalDisk", "Disk Bytes/sec", "_Total");
	perfNETs = gcnew List<PerformanceCounter^>;
	for each(std::string name in SystemAccess::GetNetAdapterNames()) {
		perfNETs->Add(gcnew PerformanceCounter("Network Interface", "Bytes Total/sec", gcnew String(name.c_str())));
	}
}

SystemAccess::~SystemAccess() {
	perfCPU->Close();
	perfHDD->Close();
	for each(PerformanceCounter^ perf in *perfNETs) {
		perf->Close();
	}
}

float SystemAccess::GetMetric(SystemMetric s) {
	try {
		switch (s) {
		case SystemMetric::CPU:
			return getCpuUsage();
		case SystemMetric::RAM:
			return getRamUsage();
		case SystemMetric::NETWORK:
			return getNetworkUsage();
		case SystemMetric::HDD:
			return getHddUsage();
		}
	}
	catch (Exception^ ex) {
		DEBUG("Could not get Metric!");
		DEBUG("Error Details: " + ex->Message + "\n" + ex->Data + "\n" + ex->Source);
	}
	return 0.0f;
}

void SystemAccess::StartESM()
{
	DEBUG("ESM will start now");
	/*
	Different Power-save modes:
		-Hibernate
			Indicates a system hibernation power mode. When a system enters hibernation, the contents of its memory are saved to disk before the computer is turned off.
			When the system is restarted, the desktop and previously active programs are restored.
		-Suspend
			Indicates a system suspended power mode. When a system is suspended, the computer switches to a low-power state called standby.
			When a computer is in standby mode, some devices are turned off and the computer uses less power.
			The system can restore itself more quickly than returning from hibernation.
			Because standby does not save the memory state to disk, a power failure while in standby can cause loss of information.
	*/
	Application::SetSuspendState(PowerState::Suspend, false, false);
}

std::vector<std::string> SystemAccess::GetRunningProccesses() {
	std::vector<std::string> list(1);
	const size_t maxPids = 1024;

	DWORD pids[maxPids] = {};
	DWORD bytesReturned = 0;
	if (::EnumProcesses(pids, sizeof pids, &bytesReturned))
	{
		DWORD cProcesses = bytesReturned / sizeof *pids;
		for (DWORD i = 0; i < cProcesses; i++)
		{
			DWORD pid = pids[i];
			if (HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid))
			{
				WCHAR filename[MAX_PATH] = {};
				if (::GetModuleFileNameEx(hProcess, NULL, (LPSTR)filename, MAX_PATH)) {
					list.push_back((std::string)(LPSTR)filename);
				}
				::CloseHandle(hProcess);
			}
		}
	}
	return list;
}

void SystemAccess::SetPresentationMode(boolean state) {
	if (state) {
		SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);
	}
	else {
		SetThreadExecutionState(ES_CONTINUOUS);
	}
}

void SystemAccess::SetAutoStart(boolean value) {
	using namespace Microsoft::Win32;
	RegistryKey^ rk;
	String^ path = "\"" + Application::ExecutablePath + "\"";
	//LocalMaschine require administrator rights
	rk = Registry::CurrentUser->OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);
	if (value) {
		rk->SetValue(APPLICATION_NAME, path);
	}
	else {
		rk->SetValue(APPLICATION_NAME, "");
	}
}

boolean SystemAccess::IsInAutoStart() {
	String^ path = "\"" + Application::ExecutablePath + "\"";
	using namespace Microsoft::Win32;
	RegistryKey^ rk;
	//Local machine require administrator rights
	rk = Registry::CurrentUser->OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);
	System::Object^ o = nullptr;
	o = rk->GetValue(APPLICATION_NAME, "");
	if (o == nullptr || o->ToString()->Length == 0 || o->ToString() != path)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<std::string> SystemAccess::GetNetAdapterNames() {
	System::String ^filter = gcnew System::String("MS TCP Loopback interface");
	std::vector<std::string> *nics = new std::vector<std::string>();
	PerformanceCounterCategory^ category = gcnew PerformanceCounterCategory("Network Interface");
	if (category->GetInstanceNames() != __nullptr)
	{
		for each (System::String ^nic in category->GetInstanceNames())
		{
			if (!nic->Equals(filter))
			{
				nics->push_back(BasicFunc::StringToString(nic));
			}
		}
	}
	return *nics;
}

float SystemAccess::GetLastInputTime() {
	//add user32.lib To Dependencies!!
	int systemUptime = Environment::TickCount;
	float idleTicks = 0;
	LASTINPUTINFO lastInputInfo;
	lastInputInfo.cbSize = (UInt32)sizeof(lastInputInfo);
	lastInputInfo.dwTime = 0;

	if (GetLastInputInfo(&lastInputInfo))
	{
		float lastInputTicks = (float)lastInputInfo.dwTime;
		idleTicks = systemUptime - lastInputTicks;
	}
	return idleTicks;
}