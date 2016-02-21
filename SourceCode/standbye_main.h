#pragma once
#include "stdafx.h"
#include "resource1.h"
#include "TimeoutWindow.h"
#include "SystemAccess.h"
#include "SystemMetricWatcher.h"
#include "MetroSettingsForm.h"
#include "MessageWindow.h"
#include "InputMonitor.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);
using namespace StandBye;
public ref class mainApplication {
private:
	NotifyIcon^ trayicon;
	MenuItem^ PresentationModeItem; //Has to be accessed
	MetroSettingsForm^ settingsForm;
	SystemMetricWatcher^ system_watcher;
	SettingsProvider* settings_provider;
	SystemAccess^ system_access;
	InputMonitor^ input_monitor;

	bool inPresentationMode;
	bool onExit;

public:
	mainApplication(HINSTANCE hInstance);
	NotifyIcon^ GenerateIcon(HINSTANCE hInstance);
	void CheckUsage();

private:
	void OpenSettings(Object^ s, System::EventArgs^ event_args);
	void Quit(Object^ s, System::EventArgs^ event_args);
	void SetPresentationMode(Object^ s, System::EventArgs^ event_args);
	ContextMenu^ GetContextMenu();
	void OnThreadException(System::Object^ sender, System::Threading::ThreadExceptionEventArgs^ args);
	void OnMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
	void OpenDebugForm(System::Object ^sender, System::EventArgs ^e);
};

ref class NotifyIconAppContext : System::Windows::Forms::ApplicationContext {
public:
	NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst);
};
