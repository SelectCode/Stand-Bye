#include "SystemTimeMonitor.h"
#include "standbye_main.h"

SystemTimeMonitor::SystemTimeMonitor(mainApplication^ sender, SettingsProvider* setProv)
{
	parent = sender;
	settings_provider = setProv;
}

void SystemTimeMonitor::Start()
{
	exit = false;
	//Starts new Thread
	MonThread = gcnew Thread(gcnew ThreadStart(this, &SystemTimeMonitor::MonitorTime));
	MonThread->IsBackground = true;
	MonThread->Start();
}

void SystemTimeMonitor::Reset()
{
	this->Stop();
	this->Start();
}

void SystemTimeMonitor::Stop()
{
	//Stops Thread
	exit = true;
	MonThread->Abort();
	MonThread->Join();
}

void SystemTimeMonitor::MonitorTime()
{
	while (!exit) {
		if ((DateTime::Now.Hour == standbyTime.Hour) && (DateTime::Now.Minute == standbyTime.Minute)) {
			parent->CheckUsage();
		}
	}
}