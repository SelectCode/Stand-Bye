#pragma once
#include "stdafx.h"
#include "resource1.h"
#include <iostream>
#include <array>
#include "TimeoutWindow.h"
#include "SystemAccess.h"
#include "SystemMetricWatcher.h"
#include "InputMonitor.h"
#include "MetroSettingsForm.h"

ref class NotifyIconAppContext : System::Windows::Forms::ApplicationContext {
public:
	NotifyIconAppContext(HINSTANCE hinst);
};

HWND hwnd;
gcroot<SystemMetricWatcher^> system_watcher;
SettingsProvider* settings_provider;
gcroot<InputMonitor^> input_monitor;
boolean inPresentationMode;
bool onExit;

void SettingsOpend(Object^ s, System::EventArgs^ event_args);
void Quit(Object^ s, System::EventArgs^ event_args);
void PresentationMode(Object^ s, System::EventArgs^ event_args);

ContextMenu^ GetContextMenu();
NotifyIcon^ GenerateIcon(HINSTANCE hInstance);
void CheckUsage();
void OnThreadException(System::Object^ sender, System::Threading::ThreadExceptionEventArgs^ args);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);
