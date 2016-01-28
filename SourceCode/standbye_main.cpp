#include "stdafx.h"
#include "standbye_main.h"

//TODO: single instance application? https://support.microsoft.com/en-us/kb/243953
//TODO: Implement Updates --> Download .txt from git hub which defines the newest version. (http://stackoverflow.com/questions/4604663/download-single-files-from-github) https://raw.githubusercontent.com/flobaader/Stand-Bye/gh-pages/index.html
//TODO: delete vector with delete[] XY
//TODO: Migrate to System::String?
//TODO: Cancel MessageWindow on mouse movement
//TODO: Debug Form
//TODO: Implement Log System
//TODO: Implement statistics
//TODO: Discussion: Use perfMon to read RAM Usage?
//TODO: Discuss the standard values
//TODO: Watcher --> analyses the average usage
//TODO: Always standby after f. ex. 10 o clock
//TODO: Implement message window and make a welcome and good bye message
//TODO: Message after Canceling the Standby Countdown: would you like to enable the presentation mode?
//TODO: Names and Copyright in all files
//TODO: pictures and team description
//TODO: booth design
//TODO: umfrage

#define threshold(X) settings_provider->getThreshold(SettingName::X)
#define active(X) settings_provider->isActive(SettingName::X)
#define sysMetric(X) system_watcher->GetSystemMetric(SystemAccess::SystemMetric::X)
using namespace SmartLogout;

NotifyIconAppContext::NotifyIconAppContext(HINSTANCE hinst) {
	GenerateIcon(hinst);
}

void SettingsOpend(Object^, System::EventArgs^) {
	using namespace SmartLogout;
	MetroSettingsForm^ settings_form = gcnew MetroSettingsForm(system_watcher, settings_provider);
	if (settings_form->ShowDialog() == ::DialogResult::OK) {
		input_monitor->Reset();
	}

	delete settings_form;
}

void Quit(Object^, System::EventArgs^) {
	onExit = true;
	input_monitor->Stop();
	delete  system_watcher, input_monitor, settings_provider;
	System::Windows::Forms::Application::Exit();
}

void PresentationMode(Object^ s, System::EventArgs ^)
{
	MenuItem^ item = (MenuItem^)s;
	if (item->Checked == false) {
		SystemAccess::SetPresentationMode(true);
		item->Checked = true;
	}
	else {
		SystemAccess::SetPresentationMode(false);
		item->Checked = false;
	}
	inPresentationMode = item->Checked;
}

void CheckUsage() {
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

	TimeoutWindow^ msgWnd = gcnew TimeoutWindow(15);

	if ((msgWnd->ShowDialog()) == (::DialogResult::OK)) {
		DEBUG("Going to Sleep mode!");
		SystemAccess::StartESM();
	}
}

ContextMenu^ GetContextMenu() {
	using namespace System::Windows::Forms;

	ContextMenu^ contextMenu = gcnew ContextMenu();

	MenuItem^ settingsItem = gcnew MenuItem();
	settingsItem->Text = "&Settings\0";
	settingsItem->Click += gcnew System::EventHandler(&SettingsOpend);

	MenuItem^ PresentationModeItem = gcnew MenuItem();
	PresentationModeItem->Text = "&Presentation mode\0";
	PresentationModeItem->Checked = false;
	PresentationModeItem->Click += gcnew System::EventHandler(&PresentationMode);

	MenuItem^ exitItem = gcnew MenuItem();
	exitItem->Text = "&Exit\0";
	exitItem->Click += gcnew System::EventHandler(&Quit);

	contextMenu->MenuItems->Add(settingsItem);
	contextMenu->MenuItems->Add(PresentationModeItem);
	contextMenu->MenuItems->Add(exitItem);

	return contextMenu;
}

NotifyIcon^ GenerateIcon(HINSTANCE hInstance) {
	using namespace System::Windows::Forms;
	::NotifyIcon^ icon = gcnew NotifyIcon();
	icon->Icon = System::Drawing::Icon::FromHandle((IntPtr)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	icon->Text = "Stand-Bye";
	icon->ContextMenu = GetContextMenu();
	icon->Visible = true;
	return icon;
}

void OnThreadException(System::Object ^ sender, System::Threading::ThreadExceptionEventArgs ^ args) {
	//TODO: Implement on exception
}

[STAThread] //Because of FileDialog --> Application is single threaded - Windows needs that
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
	Application::ThreadException += gcnew System::Threading::ThreadExceptionEventHandler(&OnThreadException);
	//Application::SetUnhandledExceptionMode(ThrowException)

	onExit = false;

	while (onExit == false) {
		settings_provider = new SettingsProvider();
		system_watcher = gcnew SystemMetricWatcher(settings_provider, 2, 30);//Sample 2 times/second, space for 30 samples, average over 15 seconds
		system_watcher->Start();
		input_monitor = gcnew InputMonitor(settings_provider, &CheckUsage);

		using System::Windows::Forms::Application;
		ApplicationContext^ context = gcnew NotifyIconAppContext(hInstance);
		Application::ApplicationExit += gcnew System::EventHandler(&Quit);
		Application::Run(context); //Synchronous
	}
}