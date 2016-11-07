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
#include "SystemTimeMonitor.h"
#include "StartBanner.h"

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
	SystemTimeMonitor^ time_monitor;

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
		bool Log = settings_provider->isActive(SettingName::LOGGING);

		//Deletes Components
		delete input_monitor;
		delete system_access;
		delete settings_provider;
		delete PresentationModeItem;
		delete supportedLanguages;

		//Stop Monitoring Threads
		StopMetricWatcher();
		StopSystemTimeWatcher();

		//Deletes Trayicon if it exists
		if (trayicon != nullptr) {
			trayicon->Visible = false;
			delete trayicon;
		}

		//Settings form
		if (settingsForm != nullptr) {
			settingsForm->Close();
			delete settingsForm;
			settingsForm = nullptr;
		}

		//Deletes Resources
		res_man->ReleaseAllResources();
		delete res_man;

		//Deletes log files if not enabled
		if (Log) {
			LOG("successfully exited mainApplication");
		}
		else {
			BasicFunc::cleanLogFiles();
		}
	};

	//Main Function
	void Start();
	void startMetricWatcher();
	void StopMetricWatcher();
	void StartSystemTimeWatcher();
	void StopSystemTimeWatcher();

	//Context Menu public
	NotifyIcon^ GenerateIcon(HINSTANCE hInstance);
	void Quit(Object^, System::EventArgs^);
	void ReloadContextMenu();
	void OpenSettingsForm();

	//Standby Functions
	void checkSystemAndStandby(bool checkThresholds);
	bool isSystemBusy(SystemMetricWatcher^ watcher); //Uses specified SystemWatcher
	bool isSystemBusy(); //Uses standard SystemWatcher
	bool isInPresentationMode();
	void setPresentationMode(bool value);
	void askUserAndStartStandby(bool SystemTime);
	bool hasUserExited();

	//PM-Hot key
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
