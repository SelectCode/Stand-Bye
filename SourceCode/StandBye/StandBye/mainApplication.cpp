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

#include "stdafx.h"
#include "mainApplication.h"
#include "DebugForm.h" //Has to be here --> cross linking

#define threshold(X) settings_provider->getThreshold(SettingName::X)
#define active(X) settings_provider->isActive(SettingName::X)

using namespace StandBye;

NotifyIconAppContext::NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst) {
	app->GenerateIcon(hinst);
}

void mainApplication::OpenSettings(Object^, System::EventArgs^) {
	LOG("Requested to load settingsForm");
	if (settingsForm == nullptr) {
		//Shows Banner while loading
		StartBanner^ banner = gcnew StartBanner();
		banner->Show();
		banner->Activate();
		banner->BringToFront();
		banner->Refresh();
		settingsForm = gcnew MetroSettingsForm(this, settings_provider, supportedLanguages);
		banner->Close();
		delete banner;

		//Shows SettingsForm
		settingsForm->ShowDialog();
		delete settingsForm;
		settingsForm = nullptr;

		//Checks if settings were changed

		//If Sleeptime at specified time is active, starts the SystemTimeMonitor (-->maybe has changed)
		if (settings_provider->isActive(SettingName::USE_SLEEPTIME)) {
			this->StartSystemTimeWatcher();
		}
		else {
			this->StopSystemTimeWatcher();
		}
	}
	else {
		//Settings form is open
		LOG("Did not load Form: SettingsForm was visible");
		settingsForm->BringToFront();
		settingsForm->Activate();
	}
}

void mainApplication::Quit(Object^, System::EventArgs^) {
	//Enables Windows standby
	SystemAccess::EnableWindowsStandBy();
	userExited = true;
	LOG("Application starts quitting...");
	Application::ExitThread();
}

void mainApplication::ReloadContextMenu()
{
	trayicon->ContextMenu = GetContextMenu();
	LOG("Reloaded Context Menu with Language:" + CultureInfo::DefaultThreadCurrentCulture->EnglishName);
}

void mainApplication::askUserAndStartStandby(bool FromSystemTime)
{
	//Checks if the application is in presentation mode
	if (inPresentationMode) {
		LOG("Application in presentation mode! \n Canceled Sleep mode!");
		if (FromSystemTime) {
			//If the Standby is started at specified time, a special message is displayed
			String^ message = res_man->GetString("msg_canceled_of_presMode", CultureInfo::DefaultThreadCurrentCulture);
			MessageWindow^ msgPres = gcnew MessageWindow(message, MessageBoxButtons::OK);
			msgPres->ShowDialog();
			delete msgPres;
			StopSystemTimeWatcher();
		}
		return;
	}

	//Check if multiple users are logged in
	if (SystemAccess::MultiUsersPreventStandby()) {
		return;
	}

	//Starts TimeOut Window
	TimeoutWindow^ msgWnd = gcnew TimeoutWindow(this, 15);
	LOG("Preparing the TimeoutWindow");
	if (msgWnd->ShowDialog() == DialogResult::OK) {
		LOG("Going to Sleep mode!");
		SystemAccess::StartESM(settings_provider);
	}
	else {
		LOG("The User has canceled the MessageWindow!");

		//Temporary Disabled
		/*
		if (ask_Enable_PresentationMode && settings_provider->isActive(SettingName::SHOW_MESSAGES)) {
			//Asks User if he wants to enable presentation mode
			String^ message = res_man->GetString("ask_presMode", CultureInfo::DefaultThreadCurrentCulture);

			MessageWindow^ msgPres = gcnew MessageWindow(message, MessageBoxButtons::YesNo);
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
			delete msgPres;
		}
		else {
			LOG("Did not ask for presentation mode, because it has been denied once");
		}
		*/

		//Shows warning if started from system-time (= Standby at specified time)
		if (FromSystemTime) {
			String^ message = res_man->GetString("msg_standby_time_canceled", CultureInfo::DefaultThreadCurrentCulture);
			MessageWindow^ msgPres = gcnew MessageWindow(message, MessageBoxButtons::OK);
			msgPres->ShowDialog();
			delete msgPres;
			StopSystemTimeWatcher();
		}
	}
}

bool mainApplication::hasUserExited()
{
	return userExited;
}

void mainApplication::SetPresentationMode(Object^, System::EventArgs ^)
{
	if (!inPresentationMode) {
		//Activates presMode
		SystemAccess::SetPresentationMode(true);
		LOG("Presentation mode enabled");
		//Checks Item in Context Menu
		PresentationModeItem->Checked = true;
		ShowBallonTipMessage(res_man->GetString("msg_presMode_activated", CultureInfo::DefaultThreadCurrentCulture));
		inPresentationMode = true;
	}
	else {
		//If presMode is already enabled, presMode will be disabled
		SystemAccess::SetPresentationMode(false);
		LOG("Presentation mode disabled");
		//Unchecks Item in Context Menu
		PresentationModeItem->Checked = false;
		ShowBallonTipMessage(res_man->GetString("msg_presMode_deactivated", CultureInfo::DefaultThreadCurrentCulture));
		inPresentationMode = false;
	}
}

bool mainApplication::isSystemBusy() {
	//Can be launched with the standard SystemWatcher or with an selected one
	if (system_watcher != nullptr) {
		return isSystemBusy(system_watcher);
	}
	else {
		throw("SystemWatcher not initialized!");
	}
}

bool mainApplication::isSystemBusy(SystemMetricWatcher^ watcher)
{
	LOG("Checking System usage....");

	//Checks if the application is in presentation mode
	if (inPresentationMode) {
		LOG("Application in presentation mode! \n Canceled Sleep mode!");
		return true;
	}

	//Check if an exception process is running
	boolean exception_process_running = false;
	for each(std::string process in settings_provider->getProcessList()) {
		String^ ProcessName = System::IO::Path::GetFileName(gcnew String(process.c_str()));

		for each(std::string running_process in SystemAccess::GetRunningProccesses()) {
			String^ RunningProcessName = System::IO::Path::GetFileName(gcnew String(running_process.c_str()));

			if (ProcessName == RunningProcessName) {
				//One Exception Process is running
				exception_process_running = true;
				break;
			}
		}
	}

	//If an exception process is running, system is busy
	if (exception_process_running) {
		LOG("An exception process is running! \n Canceled Sleep mode!");
		return true;
	}

	//Check if sound is playing
	if ((bool)active(CHECK_SOUND)) {
		if (watcher->GetSystemMetric(SystemAccess::SystemMetric::SOUND) > 0.01) {
			LOG("SOUND level too high - standby canceled");
			return true;
		}
	}

	//Check Thresholds
	//CPU
	if ((bool)active(USE_CPU)) {
		if (threshold(MAX_CPU) < watcher->GetSystemMetric(SystemAccess::SystemMetric::CPU)) {
			LOG("CPU Usage too high - standby canceled");
			return true;
		}
	}
	//RAM
	if ((bool)active(USE_RAM)) {
		if (threshold(MAX_RAM) < watcher->GetSystemMetric(SystemAccess::SystemMetric::RAM)) {
			LOG("RAM Usage too high - standby canceled");
			return true;
		}
	}
	//HDD
	if ((bool)active(USE_HDD)) {
		if (threshold(MAX_HDD) < watcher->GetSystemMetric(SystemAccess::SystemMetric::HDD)) {
			LOG("HDD Usage too high - standby canceled");
			return true;
		}
	}
	//NET
	if ((bool)active(USE_NET)) {
		if (threshold(MAX_NET) < watcher->GetSystemMetric(SystemAccess::SystemMetric::NETWORK)) {
			LOG("NETWORK Usage too high - standby canceled");
			return true;
		}
	}

	//if the method has reached this point, the system is not busy
	return false;
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
	using namespace System::Globalization;
	using namespace System::Resources;

	ContextMenu^ contextMenu = gcnew ContextMenu();

	CultureInfo^ currentCulture = CultureInfo::DefaultThreadCurrentCulture;

	MenuItem^ settingsItem = gcnew MenuItem();
	settingsItem->Text = res_man->GetString("context_settings", currentCulture);
	settingsItem->Click += gcnew System::EventHandler(this, &mainApplication::OpenSettings);

	PresentationModeItem = gcnew MenuItem();
	PresentationModeItem->Text = res_man->GetString("context_presMode", currentCulture);
	PresentationModeItem->Checked = false;
	PresentationModeItem->Click += gcnew System::EventHandler(this, &mainApplication::SetPresentationMode);

	MenuItem^ debuggig = gcnew MenuItem();
	debuggig->Text = res_man->GetString("context_debug", currentCulture);
	debuggig->Click += gcnew System::EventHandler(this, &mainApplication::OpenDebugForm);

	MenuItem^ updates = gcnew MenuItem();
	updates->Text = res_man->GetString("context_updates", currentCulture);
	updates->Click += gcnew System::EventHandler(this, &mainApplication::CheckForUpdatesClicked);

	MenuItem^ exitItem = gcnew MenuItem();
	exitItem->Text = res_man->GetString("context_exit", currentCulture);
	exitItem->Click += gcnew System::EventHandler(this, &mainApplication::Quit);

	contextMenu->MenuItems->Add(settingsItem);
	contextMenu->MenuItems->Add(PresentationModeItem);
	contextMenu->MenuItems->Add(debuggig);
	contextMenu->MenuItems->Add(updates);
	contextMenu->MenuItems->Add(exitItem);

	return contextMenu;
}

void mainApplication::Start()
{
	ApplicationContext^ context = gcnew NotifyIconAppContext(this, hinstance);
	Application::ApplicationExit += gcnew System::EventHandler(this, &mainApplication::Quit);
	Application::Run(context); //Synchronous
	LOG("!!Application exited");
}

void mainApplication::startMetricWatcher()
{
	if (system_watcher == nullptr) {
		//Loading System Access
		system_access = gcnew SystemAccess(settings_provider);
		LOG("Loaded SystemAccess");

		//Loading SystemMetricWatcher
		system_watcher = gcnew SystemMetricWatcher(system_access);//Sample 10 times/second, space for 30 samples, average over 3 seconds
		LOG("Loaded and Started SystemMetricWatcher");
	}
}

void mainApplication::StopMetricWatcher()
{
	if (system_watcher != nullptr) {
		LOG("Stopped Metric Watcher");
		delete system_access;
		delete system_watcher;
		system_access = nullptr;
		system_watcher = nullptr;
	}
}

void mainApplication::StartSystemTimeWatcher()
{
	if (time_monitor == nullptr) {
		time_monitor = gcnew SystemTimeMonitor(this, settings_provider);
		LOG("Loaded SystemtimeMonitor");
	}
}

void mainApplication::StopSystemTimeWatcher()
{
	if (time_monitor != nullptr) {
		time_monitor->Stop();
		delete time_monitor;
		time_monitor = nullptr;
		LOG("SystemTimeMonitor has been deleted");
	}
}

NotifyIcon^ mainApplication::GenerateIcon(HINSTANCE hInstance) {
	using namespace System::Windows::Forms;
	trayicon = gcnew NotifyIcon();
	trayicon->Icon = System::Drawing::Icon::FromHandle((IntPtr)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	trayicon->Text = "Stand-Bye!";
	trayicon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &mainApplication::OnIconMouseClick);
	trayicon->BalloonTipClicked += gcnew System::EventHandler(this, &mainApplication::OnIconBalloonTipClicked);
	trayicon->ContextMenu = GetContextMenu();
	trayicon->Visible = true;
	ShowBallonTipMessage(res_man->GetString("msg_welcome", CultureInfo::DefaultThreadCurrentCulture));
	return trayicon;
}

void mainApplication::checkSystemAndStandby(bool checkThresholds)
{
	if (!checkThresholds || !this->isSystemBusy(system_watcher)) {
		this->askUserAndStartStandby(!checkThresholds);
	}
}

mainApplication::mainApplication(HINSTANCE hInstance) {
	LOG("Stand-Bye is starting!");
	this->hinstance = hInstance;

	//Loads Languages
	supportedLanguages = gcnew List<CultureInfo^>();
	supportedLanguages->Add(CultureInfo::CreateSpecificCulture("de"));
	supportedLanguages->Add(CultureInfo::CreateSpecificCulture("en"));

	//Loading SettingsProvider
	settings_provider = new SettingsProvider();
	LOG("Loaded settingsProvider");

	//Defines language
	String^ loadedLanguage = gcnew String(settings_provider->getRawSetting(SettingName::LANGUAGE).c_str());

	//If language is not set, check if system language is supported
	if (loadedLanguage == "system") {
		bool language_found = false;
		for each(CultureInfo^ supLanguage in supportedLanguages) {
			if (CultureInfo::CurrentUICulture->TwoLetterISOLanguageName == supLanguage->TwoLetterISOLanguageName) {
				loadedLanguage = supLanguage->TwoLetterISOLanguageName;
				language_found = true;
			}
		}
		if (!language_found) {
			//loaded Language is not supported
			loadedLanguage = "en";
		}
	}

	//Loads Resources
	res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
	CultureInfo::DefaultThreadCurrentCulture = CultureInfo::CreateSpecificCulture(loadedLanguage);

	//Loading Input Monitor
	input_monitor = gcnew InputMonitor(this, settings_provider);
	LOG("Loaded InputMonitor");

	//Reports Instance to Server
	ServerInterface::reportInstance();

	//Loading SystemTime Monitor
	if (settings_provider->isActive(SettingName::USE_SLEEPTIME)) {
		this->StartSystemTimeWatcher();
	}

	//Checks for Updates
	Thread^ UpdateThread = gcnew Thread(gcnew System::Threading::ThreadStart(this, &mainApplication::CheckForUpdatesOnStartUp));
	UpdateThread->IsBackground = true;
	UpdateThread->Start();

	//Registers Hotkey
	this->registerPresentationModeHotkey();

	//Disable Windows intern standby
	SystemAccess::DisableWindowsStandBy();

	//Loads Debug Form if requested
	if (SystemAccess::inDebugMode()) {
		OpenDebugForm(nullptr, nullptr);
	}
}

void mainApplication::OnIconMouseClick(System::Object ^, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		//If left mouse click open settings
		this->OpenSettings(nullptr, nullptr);
	}
}

void mainApplication::OpenDebugForm(System::Object ^, System::EventArgs ^)
{
	LOG("Open DEBUG Form");
	DebugForm^ debug_form = gcnew DebugForm(this, settings_provider, input_monitor);
	debug_form->Show();
}

void mainApplication::CheckForUpdatesOnStartUp()
{
	//Updates are checked and if necessary installed
	if (settings_provider->isActive(SettingName::SEARCH_UPDATES)) {
		Updater^ updater = gcnew Updater();
		if (updater->IsUpdateAvailable()) {
			if (SystemAccess::isPortable()) {
				//Portable Update
				String^ message = res_man->GetString("msg_PortableUpdate", CultureInfo::DefaultThreadCurrentCulture);
				MessageWindow^ msg = gcnew MessageWindow(message, MessageBoxButtons::YesNo);
				//Asks to go to homepage
				if (msg->ShowDialog() == DialogResult::OK) {
					BasicFunc::openLink("www.stand-bye.de");
				}
			}
			else {
				//Standard Update
				String^ message = res_man->GetString("ask_update", CultureInfo::DefaultThreadCurrentCulture);
				MessageWindow^ msg = gcnew MessageWindow(message, MessageBoxButtons::YesNo);
				if (msg->ShowDialog() == DialogResult::OK) {
					updater->UpdateApplication(this);
				}
			}
		}
		else {
			//Deletes File if it exists
			updater->deleteInstallFile();
		}
		delete updater;
	}
}

void mainApplication::CheckForUpdatesClicked(System::Object ^, System::EventArgs ^)
{
	Updater^ updater = gcnew Updater();
	if (updater->IsUpdateAvailable()) {
		updater->UpdateApplication(this);
	}
	else {
		String^ message = res_man->GetString("application_upToDate", CultureInfo::DefaultThreadCurrentCulture);
		MessageWindow^ msg = gcnew MessageWindow(message, MessageBoxButtons::OK);
		msg->ShowDialog();
	}
	delete updater;
}

void mainApplication::OnIconBalloonTipClicked(System::Object ^, System::EventArgs ^)
{
	this->OpenSettingsForm();
}

void mainApplication::ShowBallonTipMessage(System::String ^ text)
{
	if (settings_provider->isActive(SettingName::SHOW_MESSAGES)) {
		trayicon->ShowBalloonTip(500, "Stand-Bye!", text, System::Windows::Forms::ToolTipIcon::Info);
	}
}

void mainApplication::registerPresentationModeHotkey() {
	//If the Hot key is successfully registered, add a message filter
	// MOD_ALT and MOD_CONTROL mean that alt and ctrl have to be pressed
	// MOD_NOREPEAT avoids multiple messages from one keystroke
	//0x50 is the virtual key code for the key P
	if (RegisterHotKey(NULL, GlobalAddAtom((LPCWSTR)"stand-bye\0"), (MOD_ALT | MOD_CONTROL | MOD_NOREPEAT), 0x50)) {
		LOG("Hotkey registered, adding MSG Filter");

		//Generate a new Message filter, add it to the thread
		Application::AddMessageFilter(gcnew HotKeyMessageFilter(this));
	}
	else {
		LOG("Failed to register hotkey. Error: " + GetLastError());
	}
}