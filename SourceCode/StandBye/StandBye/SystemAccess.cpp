//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader, Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//Has to be here!
#include <mmdeviceapi.h> // To get audio volume
#include <endpointvolume.h> // To get audio volume
#include "SystemAccess.h"

#define EXIT_ON_ERROR(hr) \
if (FAILED(hr)){LOG("AUDIO LEVEL DETECTION FAILED"); return 0.0f;}

SystemAccess::SystemAccess(SettingsProvider* p)
{
	LOG("Loading SystemAccess instance...");
	setprov = p;

	//Enables autostart if first launch
	if (setprov->isFirstStart() && !(bool)PORTABLE_VERSION) {
		this->SetAutoStart(true);
		LOG("Enabled autostart on first launch of the application");
	}

	perfCPU = gcnew PerformanceCounter("Processor", "% Processor Time", "_Total");
	perfHDD = gcnew PerformanceCounter("PhysicalDisk", "Disk Bytes/sec", "_Total");
	perfNETs = gcnew List<PerformanceCounter^>;
	for each(std::string name in SystemAccess::GetNetAdapterNames()) {
		perfNETs->Add(gcnew PerformanceCounter("Network Interface", "Bytes Total/sec", gcnew String(name.c_str())));
	}
}
float SystemAccess::getCPUUsage() {
	//Note: performance counters need administrator privileges at Windows Vista
	float cpuUsage_percent = perfCPU->NextValue();
	return cpuUsage_percent;
}

float SystemAccess::getRAMUsage()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	ULONGLONG totalPhysMem = memInfo.ullTotalPhys;
	ULONGLONG usedPhysMem = totalPhysMem - memInfo.ullAvailPhys;
	return (float)(100.0 * usedPhysMem / totalPhysMem);
}

float SystemAccess::getNETUsage() {
	float kbytes_per_sec = 0;
	for each(PerformanceCounter^ perf in *perfNETs) {
		kbytes_per_sec += perf->NextValue() / 1000;
	}
	return kbytes_per_sec;
}

float SystemAccess::getHDDUsage()
{
	float kbytes_per_sec = perfHDD->NextValue() / 1000;
	return kbytes_per_sec;
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
			return getCPUUsage();
		case SystemMetric::RAM:
			return getRAMUsage();
		case SystemMetric::NETWORK:
			return getNETUsage();
		case SystemMetric::HDD:
			return getHDDUsage();
		case SystemMetric::SOUND:
			return getAudioPeak();
		}
	}
	catch (Exception^ ex) {
		LOG("Could not get Metric!");
		LOG("Error Details: " + ex->Message + "\n" + ex->Data + "\n" + ex->Source);
	}
	return 0.0f;
}

void SystemAccess::StartESM()
{
	LOG("ESM will start now");
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
	std::vector<std::string> list;
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
					std::string path = (std::string)(LPSTR)filename;
					String^ SPath = gcnew String(path.c_str());
					//Filters all System32 processes
					if (!SPath->Contains("System32")) {
						list.push_back(path);
					}
				}
				::CloseHandle(hProcess);
			}
		}
	}
	return list;
}

void SystemAccess::SetPresentationMode(boolean state) {
	if (state) {
		SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED); //Application requires screen and system online
	}
	else {
		SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED); //reset the requirements
	}
}

void SystemAccess::SetAutoStart(boolean value) {
	using namespace Microsoft::Win32;
	RegistryKey^ rk;
	String^ path = "\"" + Application::ExecutablePath + "\"";
	//LocalMaschine require administrator rights
	rk = Registry::CurrentUser->OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);
	if (value) {
		rk->SetValue(APP_NAME, path);
		LOG("The autostart has been set");
	}
	else {
		rk->SetValue(APP_NAME, "");
		LOG("The autostart has been disabled");
	}
}

void SystemAccess::EnableWindowsStandBy()
{
	SetThreadExecutionState(ES_CONTINUOUS);
	LOG("Re-Enabled Windows Standby!");
}

void SystemAccess::DisableWindowsStandBy()
{
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
	LOG("Disabled Windows Standby!");
}

bool SystemAccess::isUserActive()
{
	//DWORD ActiveSessionID = WTSGetActiveConsoleSessionId();
	/*

You can call WTSGetActiveConsoleSessionId to get the terminal services (aka "fast user switching" aka "remote desktop") session ID that is currently active on the physical console.

You can call WTSQuerySessionInformation with WTS_CURRENT_SESSION for the session identifier and WTSSessionId for WTSInfoClass to get the terminal services session ID for the current process.

If the active session ID and the current process session ID are the same, the user corresponding to the current process has the active session on the physical console.

If what you want to know is whether the session that the current process is running in is active (but not necessarily on the physical console) you can instead use the WTSConnectState option to WTSQuerySessionInformation.

	*/

	//	DWORD SessionID;
		//WTSQuerySessionInformation(WTS_CURRENT_SESSION, SessionID, WTSSessionId, )
	return true;
}

bool SystemAccess::IsInAutoStart() {
	String^ path = "\"" + Application::ExecutablePath + "\"";
	using namespace Microsoft::Win32;
	RegistryKey^ rk;
	//Local machine require administrator rights
	rk = Registry::CurrentUser->OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);
	System::Object^ o = nullptr;
	o = rk->GetValue(APP_NAME, "");
	if (o == nullptr || o->ToString()->Length == 0 || o->ToString() != path)
	{
		return false;
	}
	else
	{
		return true;
	}
}

float SystemAccess::getAudioPeak()
{
	//Requires Win Vista, <mmdeviceapi.h>, <endpointvolume.h> and ole32.lib, needs to be in method to convert MeterInformation to void**
	float peak = 0;
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL; //Get Audio Interface
	IAudioMeterInformation *pMeterInfo = NULL;
	hr = CoInitialize(NULL);
	// Get enumerator for audio endpoint devices.
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator);
	EXIT_ON_ERROR(hr);
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	EXIT_ON_ERROR(hr);
	hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
		CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	EXIT_ON_ERROR(hr);
	pMeterInfo->GetPeakValue(&peak); //Gets peak value
	return peak;
}

List<String^>^ SystemAccess::getLoggedInUsers()
{
	List<String^>^ loggedInUsers = gcnew List<String^>();

	//Gets list of logged in users
	DWORD session_id;
	DWORD session_count = 0;
	WTS_SESSION_INFOA *pSession = NULL;

	//Enumerate through all sessions!
	if (!WTSEnumerateSessionsA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSession, &session_count))
	{
		LOG("Error on enumerating through sessions!");
		return loggedInUsers;
	}

	//Lists all users
	for (unsigned int i = 0; i < session_count; i++)
	{
		session_id = pSession[i].SessionId;
		// Get user name of this process
		WCHAR* pUserName;
		DWORD user_name_len = 0;

		if (WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, session_id, WTSUserName, &pUserName, &user_name_len))
		{
			String^ username = gcnew String(pUserName);
			if (username != "") {
				//Got user name successfully!
				loggedInUsers->Add(username);
			}
		}
		else {
			LOG("Error on getting username for {" + gcnew String(pUserName) + "}");
			continue;
		}
		//Free memory
		if (pUserName) WTSFreeMemory(pUserName);
	}
	WTSFreeMemory(pSession);

	LOG("Found total amount of {" + loggedInUsers->Count + "} Users:");
	for each(String^ username in loggedInUsers) {
		if (username != "") {
			LOG("\t" + username);
		}
	}

	return loggedInUsers;
}

String ^ SystemAccess::getActiveUser()
{
	String^ activeUser = gcnew String("");

	//Gets list of logged in users
	DWORD session_id;
	DWORD session_count = 0;
	WTS_SESSION_INFO *pSession = NULL;

	//Enumerate through all sessions!
	if (!WTSEnumerateSessionsA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pSession, &session_count))
	{
		LOG("Error on enumerating through sessions!");
		return "";
	}

	//Lists all users
	for (unsigned int i = 0; i < session_count; i++)
	{
		session_id = pSession[i].SessionId;

		WTS_CONNECTSTATE_CLASS wts_connect_state = WTSDisconnected;
		WTS_CONNECTSTATE_CLASS* ptr_wts_connect_state = NULL;

		// Get user name of this process
		WCHAR* pUserName;
		DWORD user_name_len = 0;

		if (WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, session_id, WTSUserName, &pUserName, &user_name_len))
		{
			String^ username = gcnew String(pUserName);
			if (username != "") {
				//Got user name successfully!

				DWORD bytes_returned = 0;
				if (::WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, session_id, WTSConnectState, reinterpret_cast<LPTSTR*>(&ptr_wts_connect_state), &bytes_returned))
				{
					wts_connect_state = *ptr_wts_connect_state;
					::WTSFreeMemory(ptr_wts_connect_state);
					if (wts_connect_state == WTSActive) {
						if (activeUser == "") {
							activeUser = username;
							LOG("The active user is: {" + activeUser + "}");
						}
						else {
							//active User already set;
							LOG("Found two or more active users!");
							return username;
						}
					}
				}
				else {
					LOG("Error on getting active state for {" + gcnew String(pUserName) + "}");
					continue;
				}
			}
		}

		//Free memory
		if (pUserName) WTSFreeMemory(pUserName);
	}
	WTSFreeMemory(pSession);

	return activeUser;
}

String ^ SystemAccess::getStartUserOfStandbye()
{
	String^ ThreadStartedUser;
	//Gets the user name, who started the Thread
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)name, &size);
	ThreadStartedUser = gcnew String(name);
	LOG("The User: {" + ThreadStartedUser + "} started Standbye!");
	return ThreadStartedUser;
}

bool SystemAccess::MultiUsersPreventStandby()
{
	//Needs Wtsapi32.h
	String^ ThreadStartedUser = getStartUserOfStandbye();
	List<String^>^ loggedInUsers = getLoggedInUsers();
	String^ currentActiveUser = getActiveUser();

	//Ready
	//////////////////////////////////////////////////////////////////////////
	/*
	Cases:
		Current User	Amount & List	Standby
		A				1(A)			yes
		-				1(A)			yes
		B				2(A,B)			no
		-				2(A,B)			no (?)

	*/
	//////////////////////////////////////////////////////////////////////////

	if (loggedInUsers->Count == 1) {
		//Only one user is active! --> The standby can be activated
		LOG("Only one user is active! StandBye can proceed!");
		return false;
	}
	else if (currentActiveUser == ThreadStartedUser) {
		//There are multiple users logged in, but the active user is the one, who started the process
		LOG("There are multiple users active, but StandBye user is active!");
		return false;
	}
	else {
		//There are multiple users active and no one is active or an other one is active
		LOG("There are multiple users logged in with a configuration that cancels standby");
		return true;
	}
}

String^ SystemAccess::getStandByeFolderPath()
{
	using namespace System::IO;
	if (!(bool)PORTABLE_VERSION) {
		//Gets the AppData Path
		String^ folder = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);
		System::IO::Directory::CreateDirectory(folder);
		folder = Path::Combine(folder, "StandBye");
		//Ensures that the folder exists

		return folder;
	}
	else {
		String^ folder = Directory::GetCurrentDirectory();
		try
		{
			// Attempt to get a list of security permissions from the folder.
			// This will raise an exception if the path is read only or do not have access to view the permissions.
			Directory::GetAccessControl(folder);

			//is authorized
			return folder;
		}
		catch (UnauthorizedAccessException^)
		{
			//Not authorized
			LOG("Not authorized to write to folder!");
			return folder;
		}
	}
}

std::vector<std::string> SystemAccess::GetNetAdapterNames() {
	System::String ^filter = gcnew System::String("MS TCP Loopback interface");
	std::vector<std::string> *nics = new std::vector<std::string>();
	PerformanceCounterCategory^ category = gcnew PerformanceCounterCategory("Network Interface");
	LOG("Get Network Adapter Names:");
	if (category->GetInstanceNames() != __nullptr)
	{
		for each (System::String ^nic in category->GetInstanceNames())
		{
			if (!nic->Equals(filter))
			{
				nics->push_back(BasicFunc::StringToString(nic));
				LOG("\t" + nic);
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