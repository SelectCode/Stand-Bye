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
#define sysMetric(X) system_watcher->GetSystemMetric(SystemAccess::SystemMetric::X)

using namespace StandBye;

NotifyIconAppContext::NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst) {
	app->GenerateIcon(hinst);
}

void mainApplication::OpenSettings(Object^, System::EventArgs^) {
	LOG("Started opening SettingsForm");
	if (settingsForm == nullptr) {
		//Ensures that settingsForm != nullptr
		settingsForm = gcnew MetroSettingsForm(this, system_watcher, settings_provider, system_access, input_monitor, supportedLanguages);
		settingsForm->Show();
	}
	else if (settingsForm->IsDisposed) {
		settingsForm = gcnew MetroSettingsForm(this, system_watcher, settings_provider, system_access, input_monitor, supportedLanguages);
		settingsForm->Show();
	}
	else {
		LOG("Did not load Form: SettingsForm was visible");
		settingsForm->BringToFront();
		settingsForm->Activate();
	}
}

void mainApplication::Quit(Object^, System::EventArgs^) {
	LOG("Application starts quitting...");
	userExited = true;
	input_monitor->Stop();
	LOG("Stopped InputMonitor");
	trayicon->Visible = false;
	LOG("ByeBye...");
	instance_monitor->Destroy();
}

void mainApplication::ReloadContextMenu()
{
	trayicon->ContextMenu = GetContextMenu();
	LOG("Reloaded Context Menu with Language:" + CultureInfo::DefaultThreadCurrentCulture->EnglishName);
}

void mainApplication::askUserAndStartStandby()
{
	//Checks if the application is in presentation mode
	if (inPresentationMode) {
		LOG("Application in presentation mode! \n Canceled Sleep mode!");
		return;
	}

	//Check if multiple users are logged in
	if (SystemAccess::MultiUsersPreventStandby()) {
		return;
	}

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
		}
		else {
			LOG("Did not ask for presentation mode, because it has been denied once");
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
		SystemAccess::SetPresentationMode(true);
		LOG("Presentation mode enabled");
		PresentationModeItem->Checked = true;
		ShowBallonTipMessage(res_man->GetString("msg_presMode_activated", CultureInfo::DefaultThreadCurrentCulture));
		inPresentationMode = true;
	}
	else {
		SystemAccess::SetPresentationMode(false);
		LOG("Presentation mode disabled");
		PresentationModeItem->Checked = false;
		ShowBallonTipMessage(res_man->GetString("msg_presMode_deactivated", CultureInfo::DefaultThreadCurrentCulture));
		inPresentationMode = false;
	}
}

bool mainApplication::isSystemBusy()
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
		if (BasicFunc::VectorContains(SystemAccess::GetRunningProccesses(), process)) {
			exception_process_running = true;
			break;
		}
	}

	if (exception_process_running) {
		LOG("An exception process is running! \n Canceled Sleep mode!");
		return true;
	}

	//Check if sound is playing
	if ((bool)active(CHECK_SOUND)) {
		if (sysMetric(SOUND) > 0.01) {
			LOG("SOUND level too high - standby canceled");
			return true;
		}
	}

	//Check Thresholds
	//CPU
	if ((bool)active(USE_CPU)) {
		if (threshold(MAX_CPU) < sysMetric(CPU)) {
			LOG("CPU Usage too high - standby canceled");
			return true;
		}
	}
	//RAM
	if ((bool)active(USE_RAM)) {
		if (threshold(MAX_RAM) < sysMetric(RAM)) {
			LOG("RAM Usage too high - standby canceled");
			return true;
		}
	}
	//HDD
	if ((bool)active(USE_HDD)) {
		if (threshold(MAX_HDD) < sysMetric(HDD)) {
			LOG("HDD Usage too high - standby canceled");
			return true;
		}
	}
	//NET
	if ((bool)active(USE_NET)) {
		if (threshold(MAX_NET) < sysMetric(NETWORK)) {
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

void mainApplication::checkSystemAndStandby()
{
	if (!this->isSystemBusy()) {
		this->askUserAndStartStandby();
	}
}

mainApplication::mainApplication(HINSTANCE hInstance) {
	LOG("Stand-Bye is starting!");

	//Loads Languages
	supportedLanguages = gcnew List<CultureInfo^>();
	supportedLanguages->Add(CultureInfo::CreateSpecificCulture("de"));
	supportedLanguages->Add(CultureInfo::CreateSpecificCulture("en"));

	instance_monitor = gcnew InstanceMonitor(this);

	//If another instance is running --> exit
	if (instance_monitor->isAnotherInstanceRunning()) {
		LOG("Application quits because of other instance");
		userExited = true;
	}

	try {
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
		res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
		CultureInfo::DefaultThreadCurrentCulture = CultureInfo::CreateSpecificCulture(loadedLanguage);

		delete loadedLanguage;

		//Loading System Access
		system_access = gcnew SystemAccess(settings_provider);
		LOG("Loaded SystemAccess");

		//Loading SystemMetricWatcher
		system_watcher = gcnew SystemMetricWatcher(system_access, 5, 30);//Sample 10 times/second, space for 30 samples, average over 3 seconds
		LOG("Loaded and Started SystemMetricWatcher");

		//Loading Input Monitor
		input_monitor = gcnew InputMonitor(this, settings_provider);
		LOG("Loaded InputMonitor");

		//Checks for Updates
		UpdateThread = gcnew Thread(gcnew System::Threading::ThreadStart(this, &mainApplication::CheckForUpdatesOnStartUp));
		UpdateThread->IsBackground = true;
		UpdateThread->Start();

		//Disable Windows intern standby
		SystemAccess::DisableWindowsStandBy();

		ApplicationContext^ context = gcnew NotifyIconAppContext(this, hInstance);
		Application::ApplicationExit += gcnew System::EventHandler(this, &mainApplication::Quit);
		Application::Run(context); //Synchronous
		LOG("!!Application exited");
	}
	catch (Exception^ e) {
		//Catching Exception
		LOG("Exception occured!");
		LOG(e->Message);
		LOG(e->Data->ToString());
		LOG(e->HelpLink);
	}

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
			String^ message = res_man->GetString("ask_update", CultureInfo::DefaultThreadCurrentCulture);
			MessageWindow^ msg = gcnew MessageWindow(message, MessageBoxButtons::YesNo);
			if (msg->ShowDialog() == DialogResult::OK) {
				updater->UpdateApplication(this);
			}
		}
		delete updater;
	}
	delete UpdateThread;
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
		trayicon->ShowBalloonTip(1000, "Stand-Bye!", text, System::Windows::Forms::ToolTipIcon::Info);
	}
}