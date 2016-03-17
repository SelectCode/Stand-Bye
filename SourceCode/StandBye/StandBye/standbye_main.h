//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: standbye_main.h
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow);

using namespace StandBye;
using System::Resources::ResourceManager;
using System::Globalization::CultureInfo;
using System::Windows::Forms::Application;

public ref class mainApplication {
private:
	NotifyIcon^ trayicon;
	MenuItem^ PresentationModeItem; //Has to be accessed
	MetroSettingsForm^ settingsForm;
	SystemMetricWatcher^ system_watcher;
	SettingsProvider* settings_provider;
	SystemAccess^ system_access;
	InputMonitor^ input_monitor;
	InstanceMonitor^ instance_monitor;

	//Resources and Languages
	ResourceManager^ res_man;
	List<CultureInfo^>^ supportedLanguages;

	bool inPresentationMode = false;
	bool onExit = false;
	bool ask_Enable_PresentationMode = true;

public:
	mainApplication(HINSTANCE hInstance);
	~mainApplication()
	{
		delete settingsForm, input_monitor, system_watcher, system_access, settings_provider;
	}
	NotifyIcon^ GenerateIcon(HINSTANCE hInstance);
	void CheckUsage();
	void OpenSettingsForm();
	bool isInPresentationMode();
	void setPresentationMode(bool value);
	void Quit(Object^, System::EventArgs^);
	void ReloadContextMenu();
	void prepareStandby();
private:

	void OpenSettings(Object^, System::EventArgs^);
	void SetPresentationMode(Object^, System::EventArgs^);
	ContextMenu^ GetContextMenu();
	void OnIconMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
	void OpenDebugForm(System::Object ^sender, System::EventArgs ^e);
	void CheckForUpdatesOnStartUp();
	void CheckForUpdatesClicked(System::Object ^sender, System::EventArgs ^e);
	void OnIconBalloonTipClicked(System::Object ^sender, System::EventArgs ^e);
	void ShowBallonTipMessage(System::String^ text);
};

ref class NotifyIconAppContext : System::Windows::Forms::ApplicationContext {
public:
	NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst);
};
