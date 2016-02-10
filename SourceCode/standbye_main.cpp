#include "stdafx.h"
#include "standbye_main.h"

#define threshold(X) settings_provider->getThreshold(SettingName::X)
#define active(X) settings_provider->isActive(SettingName::X)
#define sysMetric(X) system_watcher->GetSystemMetric(SystemAccess::SystemMetric::X)
using namespace StandBye;

[STAThread] //Because of FileDialog --> Application is single threaded - Windows needs that
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
	mainApplication^ standbye = gcnew mainApplication(hInstance);
}

NotifyIconAppContext::NotifyIconAppContext(mainApplication^ app, HINSTANCE hinst) {
	app->GenerateIcon(hinst);
}

void mainApplication::OpenSettings(Object^, System::EventArgs^) {
	using namespace StandBye;
	if (settingsForm->Visible) {
		return;
	}
	if (settingsForm->ShowDialog() == ::DialogResult::OK) {
		input_monitor->Reset();
	}
	//Recreates SettingsForm
	settingsForm = gcnew MetroSettingsForm(system_watcher, settings_provider);
	settingsForm->Visible = false;
}

void mainApplication::Quit(Object^, System::EventArgs^) {
	onExit = true;
	input_monitor->Stop();
	delete  system_watcher, input_monitor, settings_provider;
	System::Windows::Forms::Application::Exit();
}

void mainApplication::SetPresentationMode(Object^ s, System::EventArgs ^)
{
	MenuItem^ item = (MenuItem^)s;
	if (item->Checked == false) {
		SystemAccess::SetPresentationMode(true);
		item->Checked = true;
		trayicon->ShowBalloonTip(3000, "Stand-Bye!", "The Presentation mode has been activated!", System::Windows::Forms::ToolTipIcon::Info);
	}
	else {
		SystemAccess::SetPresentationMode(false);
		trayicon->ShowBalloonTip(3000, "Stand-Bye!", "The Presentation mode has been deactivated!", System::Windows::Forms::ToolTipIcon::Info);
		item->Checked = false;
	}
	inPresentationMode = item->Checked;
}

void mainApplication::CheckUsage() {
	if (inPresentationMode) {
		DEBUG("Application in presentation mode! \n Canceled Sleep mode!");
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
		DEBUG("An exception process is running! \n Canceled Sleep mode!");
		return;
	}

	//Check Thresholds

	if (((bool)active(USE_HDD) ? threshold(MAX_HDD) < sysMetric(HDD) : false))return;
	if (((bool)active(USE_CPU) ? threshold(MAX_CPU) < sysMetric(CPU) : false))return;
	if (((bool)active(USE_RAM) ? threshold(MAX_RAM) < sysMetric(RAM) : false))return;
	if (((bool)active(USE_NET) ? threshold(MAX_NET) < sysMetric(NETWORK) : false)) return;

	TimeoutWindow^ msgWnd = gcnew TimeoutWindow(15, settings_provider);

	if ((msgWnd->ShowDialog()) == (::DialogResult::OK)) {
		DEBUG("Going to Sleep mode!");
		SystemAccess::StartESM();
	}
	else {
		DEBUG("The User has canceled the MessageWindow!");

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

	MenuItem^ exitItem = gcnew MenuItem();
	exitItem->Text = "&Exit\0";
	exitItem->Click += gcnew System::EventHandler(this, &mainApplication::Quit);

	contextMenu->MenuItems->Add(settingsItem);
	contextMenu->MenuItems->Add(PresentationModeItem);
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

void mainApplication::OnThreadException(System::Object ^ sender, System::Threading::ThreadExceptionEventArgs ^ args) {
	//TODO: Implement on exception --> Log system
}

mainApplication::mainApplication(HINSTANCE hInstance) {
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(this, &mainApplication::OnThreadException);
	//Application::SetUnhandledExceptionMode(ThrowException)
	onExit = false;

	while (onExit == false) {
		settings_provider = new SettingsProvider();
		system_watcher = gcnew SystemMetricWatcher(settings_provider, 2, 30);//Sample 2 times/second, space for 30 samples, average over 15 seconds
		system_watcher->Start();
		input_monitor = gcnew InputMonitor(this, settings_provider);
		settingsForm = gcnew MetroSettingsForm(system_watcher, settings_provider);
		settingsForm->Visible = false;

		using System::Windows::Forms::Application;
		ApplicationContext^ context = gcnew NotifyIconAppContext(this, hInstance);
		Application::ApplicationExit += gcnew System::EventHandler(this, &mainApplication::Quit);
		Application::Run(context); //Synchronous
	}
}

void mainApplication::OnMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		mainApplication::OpenSettings(nullptr, nullptr);
	}
}