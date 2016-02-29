//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: standbye_main.cpp
 * Author: Florian Baader, Matthias Weirich
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "standbye_main.h"
#include "DebugForm.h" //Has to be here --> cross linking

#define threshold(X) settings_provider->getThreshold(SettingName::X)
#define active(X) settings_provider->isActive(SettingName::X)
#define sysMetric(X) system_watcher->GetSystemMetric(SystemAccess::SystemMetric::X)
using namespace StandBye;

[STAThread] //Because of FileDialog --> Application is single threaded - Windows needs that
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
	mainApplication^ standbye = gcnew mainApplication(hInstance);
	delete standbye;
}

NotifyIconAppContext::NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst) {
	app->GenerateIcon(hinst);
}

void mainApplication::OpenSettings(Object^, System::EventArgs^) {
	LOG("Started opening SettingsForm");
	if (settingsForm->Visible) {
		LOG("Did not load Form: SettingsForm was visible");
		settingsForm->BringToFront();
		settingsForm->Activate();
		return;
	}
	else {
		settingsForm->Visible = true;
	}
}

void mainApplication::Quit(Object^, System::EventArgs^) {
	LOG("Application starts quitting...");
	onExit = true;
	input_monitor->Stop();
	LOG("Stopped InputMonitor");
	trayicon->Visible = false;
	LOG("ByeBye...");
	instance_monitor->Destroy();
	System::Windows::Forms::Application::Exit();
}

void mainApplication::SetPresentationMode(Object^, System::EventArgs ^)
{
	if (!inPresentationMode) {
		SystemAccess::SetPresentationMode(true);
		LOG("Presentation mode enabled");
		PresentationModeItem->Checked = true;
		ShowBallonTipMessage("The Presentation mode has been activated!");
		inPresentationMode = true;
	}
	else {
		SystemAccess::SetPresentationMode(false);
		LOG("Presentation mode disabled");
		PresentationModeItem->Checked = false;
		ShowBallonTipMessage("The Presentation mode has been deactivated!");
		inPresentationMode = false;
	}
}

void mainApplication::CheckUsage() {
	LOG("Checking System state....");
	//Checks if the application is in presentation mode
	if (inPresentationMode) {
		LOG("Application in presentation mode! \n Canceled Sleep mode!");
		return;
	}
	//Check if an exception process is running
	boolean exception_process_running = false;
	for each(std::string process in settings_provider->getProcessList()) {
		if (BasicFunc::VectorContains(SystemAccess::GetRunningProccesses(), process)) {
			exception_process_running = true;
			break;
		}
	}

	if (exception_process_running) {
		LOG("An exception process is running! \n Canceled Sleep mode!");
		return;
	}

	//Check if sound is playing
	if ((bool)active(CHECK_SOUND)) {
		if (sysMetric(SOUND) > 0.01) {
			LOG("SOUND level too high - standby canceled");
			return;
		}
	}

	//Check Thresholds
	//CPU
	if ((bool)active(USE_CPU)) {
		if (threshold(MAX_CPU) < sysMetric(CPU)) {
			LOG("CPU Usage too high - standby canceled");
			return;
		}
	}
	//RAM
	if ((bool)active(USE_RAM)) {
		if (threshold(MAX_RAM) < sysMetric(RAM)) {
			LOG("RAM Usage too high - standby canceled");
			return;
		}
	}
	//HDD
	if ((bool)active(USE_HDD)) {
		if (threshold(MAX_HDD) < sysMetric(HDD)) {
			LOG("HDD Usage too high - standby canceled");
			return;
		}
	}
	//NET
	if ((bool)active(USE_NET)) {
		if (threshold(MAX_NET) < sysMetric(NETWORK)) {
			LOG("NETWORK Usage too high - standby canceled"); return;
		}
	}

	//If the method has reached this point, the standby can be started

	TimeoutWindow^ msgWnd = gcnew TimeoutWindow(15, settings_provider);
	LOG("Preparing the TimeoutWindow");
	if (msgWnd->ShowDialog() == DialogResult::OK) {
		LOG("Going to Sleep mode!");
		SystemAccess::StartESM();
	}
	else {
		LOG("The User has canceled the MessageWindow!");

		if (ask_Enable_PresentationMode) {
			//Asks User if he wants to enable presentation mode
			MessageWindow^ msgPres = gcnew MessageWindow("Do you like to enable the presentation mode?" + "\n" + "There will be no more interruptions!");
			if (msgPres->ShowDialog() == DialogResult::OK) {
				//Enable presentation mode
				SystemAccess::SetPresentationMode(true);
				PresentationModeItem->Checked = true;
				inPresentationMode = true;
				LOG("The user accepted to enable the presentation mode");
			}
			else {
				//Do nothing
				LOG("The user denied to enable the presentation mode");
				ask_Enable_PresentationMode = false;
			}
		}
		else {
			LOG("Did not ask for presentation mode, because it has been denied once");
		}
	}
}

void mainApplication::OpenSettingsForm()
{
	OpenSettings(nullptr, nullptr);
}

bool mainApplication::isInPresentationMode()
{
	return inPresentationMode;
}

void mainApplication::setPresentationMode(bool value)
{
	if (value != inPresentationMode) {
		SetPresentationMode(nullptr, nullptr); //Changes the state
	}
}

ContextMenu^ mainApplication::GetContextMenu() {
	using namespace System::Windows::Forms;

	ContextMenu^ contextMenu = gcnew ContextMenu();

	MenuItem^ settingsItem = gcnew MenuItem();
	settingsItem->Text = "&Settings\0";
	settingsItem->Click += gcnew System::EventHandler(this, &mainApplication::OpenSettings);

	PresentationModeItem = gcnew MenuItem();
	PresentationModeItem->Text = "&Presentation mode\0";
	PresentationModeItem->Checked = false;
	PresentationModeItem->Click += gcnew System::EventHandler(this, &mainApplication::SetPresentationMode);

	MenuItem^ debuggig = gcnew MenuItem();
	debuggig->Text = "&Debugging\0";
	debuggig->Click += gcnew System::EventHandler(this, &mainApplication::OpenDebugForm);

	MenuItem^ updates = gcnew MenuItem();
	updates->Text = "&Check for Updates\0";
	updates->Click += gcnew System::EventHandler(this, &mainApplication::CheckForUpdatesClicked);

	MenuItem^ exitItem = gcnew MenuItem();
	exitItem->Text = "&Exit\0";
	exitItem->Click += gcnew System::EventHandler(this, &mainApplication::Quit);

	contextMenu->MenuItems->Add(settingsItem);
	contextMenu->MenuItems->Add(PresentationModeItem);
	contextMenu->MenuItems->Add(debuggig);
	contextMenu->MenuItems->Add(updates);
	contextMenu->MenuItems->Add(exitItem);

	return contextMenu;
}

NotifyIcon^ mainApplication::GenerateIcon(HINSTANCE hInstance) {
	using namespace System::Windows::Forms;
	trayicon = gcnew NotifyIcon();
	trayicon->Icon = System::Drawing::Icon::FromHandle((IntPtr)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	trayicon->Text = "Stand-Bye";
	trayicon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &mainApplication::OnIconMouseClick);
	trayicon->BalloonTipClicked += gcnew System::EventHandler(this, &mainApplication::OnIconBalloonTipClicked);
	trayicon->ContextMenu = GetContextMenu();
	trayicon->Visible = true;
	ShowBallonTipMessage("Standby is active. The environment will thank you!");
	return trayicon;
}

void mainApplication::OnThreadException(System::Object ^, System::Threading::ThreadExceptionEventArgs ^e) {
	LOG(e->Exception->Message + "\n" +
		e->Exception->Data + "\n" +
		e->Exception->StackTrace + "\n" +
		e->Exception->HelpLink);
}

mainApplication::mainApplication(HINSTANCE hInstance) {
	LOG("Stand-Bye is starting!");

	//Sets Exception Modes
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(this, &mainApplication::OnThreadException);
	Application::SetUnhandledExceptionMode(UnhandledExceptionMode::CatchException);

	onExit = false;
	instance_monitor = gcnew InstanceMonitor(this);

	//If another instance is running --> exit
	if (instance_monitor->isAnotherInstanceRunning()) {
		LOG("Application quits because of other instance");
		onExit = true;
	}

	while (onExit == false) {
		try {
			settings_provider = new SettingsProvider();
			LOG("Loaded settingsProvider");
			system_access = gcnew SystemAccess(settings_provider);
			LOG("Loaded SystemAccess");
			system_watcher = gcnew SystemMetricWatcher(system_access, 2, 30);//Sample 2 times/second, space for 30 samples, average over 15 seconds
			system_watcher->Start();
			LOG("Loaded and Started SystemMetricWatcher");
			input_monitor = gcnew InputMonitor(this, settings_provider);
			LOG("Loaded InputMonitor");
			settingsForm = gcnew MetroSettingsForm(this, system_watcher, settings_provider, system_access, input_monitor);
			LOG("Loaded invisible SettingsForm");

			//Checks for Updates
			CheckForUpdatesOnStartUp();

			//Disable Windows intern standby
			SystemAccess::DisableWindowsStandBy();

			using System::Windows::Forms::Application;
			ApplicationContext^ context = gcnew NotifyIconAppContext(this, hInstance);
			Application::ApplicationExit += gcnew System::EventHandler(this, &mainApplication::Quit);
			Application::Run(context); //Synchronous
			LOG("!!Application exited");
		}
		catch (Exception^ e) {
			LOG("Exception occured!");
			LOG(e->Message);
			LOG(e->Data->ToString());
			LOG(e->HelpLink);
		}
	}
	//Destroys instance monitor
	instance_monitor->Destroy();

	//Cleans up Taskbar
	trayicon->Visible = false;

	//Enables Windows standby
	SystemAccess::EnableWindowsStandBy();
}

void mainApplication::OnIconMouseClick(System::Object ^, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == Windows::Forms::MouseButtons::Left && e->Clicks == 0) {
		//If left mouse click open settings
		this->OpenSettings(nullptr, nullptr);
	}
	else if (e->Button == Windows::Forms::MouseButtons::Left && e->Clicks > 0) {
		//If Double clicked, open DebugForm
		this->OpenDebugForm(nullptr, nullptr);
	}
}

void mainApplication::OpenDebugForm(System::Object ^, System::EventArgs ^)
{
	LOG("Open DEBUG Form");
	DebugForm^ debug_form = gcnew DebugForm(this, settings_provider, system_access, input_monitor, system_watcher);
	debug_form->Show();
}

void mainApplication::CheckForUpdatesOnStartUp()
{
	//Updates are checked and if necessary installed
	if (settings_provider->isActive(SettingName::SEARCH_UPDATES)) {
		Updater^ updater = gcnew Updater();
		if (updater->IsUpdateAvailable()) {
			MessageWindow^ msg = gcnew MessageWindow("A new version of Stand-Bye! has been released!" + "\n" + "Do you want to download it?");
			if (msg->ShowDialog() == DialogResult::OK) {
				updater->UpdateApplication(this);
			}
		}
	}
}

void mainApplication::CheckForUpdatesClicked(System::Object ^, System::EventArgs ^)
{
	Updater^ updater = gcnew Updater();
	if (updater->IsUpdateAvailable()) {
		updater->UpdateApplication(this);
	}
	else {
		MessageWindow^ msg = gcnew MessageWindow("Your version is up to date!");
		msg->ShowDialog();
	}
}

void mainApplication::OnIconBalloonTipClicked(System::Object ^, System::EventArgs ^)
{
	this->OpenSettingsForm();
}

void mainApplication::ShowBallonTipMessage(System::String ^ text)
{
	if (settings_provider->isActive(SettingName::SHOW_MESSAGES)) {
		trayicon->ShowBalloonTip(1000, "Stand-Bye!", text, System::Windows::Forms::ToolTipIcon::Info);
	}
}