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
	using namespace StandBye;
	LOG("Open Settings...");
	if (settingsForm->Visible) {
		return;
	}
	if (settingsForm->ShowDialog() == ::DialogResult::OK) {
		input_monitor->Reset();
		LOG("SettingsForm returned OK");
	}
	else {
		LOG("SettingsForm returned Cancel");
	}
	//Recreates SettingsForm
	settingsForm = gcnew MetroSettingsForm(system_watcher, settings_provider);
	settingsForm->Visible = false;
	LOG("Reloaded SettingsForm (invisible)");
}

void mainApplication::Quit(Object^, System::EventArgs^) {
	LOG("Application starts quitting...");
	onExit = true;
	input_monitor->Stop();
	LOG("Stopped InputMonitor");
	delete  system_watcher, input_monitor, settings_provider;
	LOG("ByeBye...");
	System::Windows::Forms::Application::Exit();
}

void mainApplication::SetPresentationMode(Object^ s, System::EventArgs ^)
{
	MenuItem^ item = (MenuItem^)s;
	if (item->Checked == false) {
		SystemAccess::SetPresentationMode(true);
		LOG("Presentation mode enabled");
		item->Checked = true;
		trayicon->ShowBalloonTip(3000, "Stand-Bye!", "The Presentation mode has been activated!", System::Windows::Forms::ToolTipIcon::Info);
	}
	else {
		SystemAccess::SetPresentationMode(false);
		LOG("Presentation mode disabled");
		trayicon->ShowBalloonTip(3000, "Stand-Bye!", "The Presentation mode has been deactivated!", System::Windows::Forms::ToolTipIcon::Info);
		item->Checked = false;
	}
	inPresentationMode = item->Checked;
}

void mainApplication::CheckUsage() {
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
		if (sysMetric(SOUND) > 0.1) {
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
		//Asks User if he wants to enable presentation mode
		MessageWindow^ msgPres = gcnew MessageWindow("Do you like to enable the presentation mode?" + "\n" + "There will be no more interruptions!");
		if (msgPres->ShowDialog() == DialogResult::OK) {
			//Enable presentation mode
			SystemAccess::SetPresentationMode(true);
			PresentationModeItem->Checked = true;
		}
		else {
			//Do nothing
		}
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

	MenuItem^ exitItem = gcnew MenuItem();
	exitItem->Text = "&Exit\0";
	exitItem->Click += gcnew System::EventHandler(this, &mainApplication::Quit);

	contextMenu->MenuItems->Add(settingsItem);
	contextMenu->MenuItems->Add(PresentationModeItem);
	contextMenu->MenuItems->Add(debuggig);
	contextMenu->MenuItems->Add(exitItem);

	return contextMenu;
}

NotifyIcon^ mainApplication::GenerateIcon(HINSTANCE hInstance) {
	using namespace System::Windows::Forms;
	trayicon = gcnew NotifyIcon();
	trayicon->Icon = System::Drawing::Icon::FromHandle((IntPtr)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	trayicon->Text = "Stand-Bye";
	trayicon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &mainApplication::OnMouseClick);
	trayicon->ContextMenu = GetContextMenu();
	trayicon->Visible = true;
	trayicon->ShowBalloonTip(4000, "Stand-Bye!", "Standby is active. The environment will thank you!", System::Windows::Forms::ToolTipIcon::Info);
	return trayicon;
}

void mainApplication::OnThreadException(System::Object ^, System::Threading::ThreadExceptionEventArgs ^e) {
	LOG(e->Exception->Message + "\n"+
		e->Exception->Data + "\n" +
		e->Exception->StackTrace + "\n" +
		e->Exception->InnerException +
		e->Exception->HelpLink + "\n");
}

mainApplication::mainApplication(HINSTANCE hInstance) {
	LOG("Stand-Bye starts now!");
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(this, &mainApplication::OnThreadException);
	Application::SetUnhandledExceptionMode(UnhandledExceptionMode::CatchException);
	onExit = false;

	while (onExit == false) {
		settings_provider = new SettingsProvider();
		LOG("Loaded settingsProvider");
		system_watcher = gcnew SystemMetricWatcher(settings_provider, 2, 30);//Sample 2 times/second, space for 30 samples, average over 15 seconds
		system_watcher->Start();
		LOG("Loaded and Started SystemMetricWatcher");
		input_monitor = gcnew InputMonitor(this, settings_provider);
		LOG("Loaded InputMonitor");
		settingsForm = gcnew MetroSettingsForm(system_watcher, settings_provider);
		settingsForm->Visible = false;
		LOG("Loaded invisible SettingsForm");

		using System::Windows::Forms::Application;
		ApplicationContext^ context = gcnew NotifyIconAppContext(this, hInstance);
		Application::ApplicationExit += gcnew System::EventHandler(this, &mainApplication::Quit);
		Application::Run(context); //Synchronous
		LOG("!!Application exited");
	}
}

void mainApplication::OnMouseClick(System::Object ^, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		mainApplication::OpenSettings(nullptr, nullptr);
	}
}

void mainApplication::OpenDebugForm(System::Object ^, System::EventArgs ^)
{
	LOG("Open DEBUG Form");
	DebugForm^ debug_form = gcnew DebugForm(this, settings_provider, input_monitor, system_watcher);
	debug_form->Show();
}