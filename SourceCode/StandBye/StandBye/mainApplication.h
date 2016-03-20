//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader, Matthias Weirich
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "resource1.h"
#include "TimeoutWindow.h"
#include "SystemAccess.h"
#include "SystemMetricWatcher.h"
#include "MessageWindow.h"
#include "InputMonitor.h"
#include "InstanceMonitor.h"
#include "MetroSettingsForm.h"
#include "Updater.h"
#include "HotKeyMessageFilter.h"

using namespace StandBye;
using System::Resources::ResourceManager;
using System::Globalization::CultureInfo;
using System::Windows::Forms::Application;

public ref class mainApplication {
private:
	HINSTANCE hinstance;
	NotifyIcon^ trayicon;
	MenuItem^ PresentationModeItem; //Has to be accessed
	MetroSettingsForm^ settingsForm;
	SystemMetricWatcher^ system_watcher;
	SettingsProvider* settings_provider;
	SystemAccess^ system_access;
	InputMonitor^ input_monitor;
	System::Threading::Thread^ UpdateThread;

	//Resources and Languages
	ResourceManager^ res_man;
	List<CultureInfo^>^ supportedLanguages;

	bool inPresentationMode = false;
	bool userExited = false;
	bool ask_Enable_PresentationMode = true;

public:
	//Main Functions
	mainApplication(HINSTANCE hInstance);

	~mainApplication() {
		//Cleans Resources
		delete settingsForm;
		delete input_monitor;
		delete settings_provider;
		delete system_access;
		delete system_watcher;
		delete PresentationModeItem;
		delete trayicon;
		LOG("successfully exited mainApplication");
	};
	//Main Function
	void Start();

	//Context Menu public
	NotifyIcon^ GenerateIcon(HINSTANCE hInstance);
	void Quit(Object^, System::EventArgs^);
	void ReloadContextMenu();
	void OpenSettingsForm();

	//Standby Functions
	void checkSystemAndStandby();
	bool isSystemBusy();
	bool isInPresentationMode();
	void setPresentationMode(bool value);
	void askUserAndStartStandby();
	bool hasUserExited();

	//PM-Hotkey
	void registerPresentationModeHotkey();

private:
	//Context Menu & Event Handlers
	ContextMenu^ GetContextMenu();
	void OpenSettings(Object^, System::EventArgs^);
	void SetPresentationMode(Object^, System::EventArgs^);
	void OnIconMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
	void OpenDebugForm(System::Object ^sender, System::EventArgs ^e);
	void OnIconBalloonTipClicked(System::Object ^sender, System::EventArgs ^e);
	void ShowBallonTipMessage(System::String^ text);

	//Updates
	void CheckForUpdatesOnStartUp();
	void CheckForUpdatesClicked(System::Object ^sender, System::EventArgs ^e);
};

ref class NotifyIconAppContext : System::Windows::Forms::ApplicationContext {
public:
	NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst);
};
