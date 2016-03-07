//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: MetroSettingsForm.cpp
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MetroSettingsForm.h"
#include "standbye_main.h"
using namespace StandBye;

System::Void MetroSettingsForm::MetroSettingsForm_Load(System::Object^, System::EventArgs^) {
	//KeyPreview
	this->KeyPreview = true;

	//Focus on first tabPage
	metroTabControl1->SelectedTab = metroTabPageSettings;

	//Get Icon
	res_man = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);
	this->Icon = (System::Drawing::Icon^) res_man->GetObject("icon1");

	//Sets version
	String^ versionText = gcnew String("v" + APP_VERSION);
	if ((bool)PORTABLE_VERSION) {
		versionText += " PORTABLE";
	}
	versionText += "\n" + "© Florian Baader, Stephan Le, Matthias Weirich";
	metroLabelVersion->Text = versionText;

	//Resource Manager
	res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);

	//Select Language
	metroComboBoxLanguage->Text = CultureInfo::DefaultThreadCurrentCulture->NativeName;
	switchLanguage();

	//Sets preferred sizes
	tableLayoutPanelProgrammSettings->Size = tableLayoutPanelProgrammSettings->PreferredSize;

	//Activate
	this->Activate();

	//Load Settings
	metroTrackBarCPU->Value = settings_provider->getThreshold(SettingName::MAX_CPU);
	metroTrackBarRAM->Value = settings_provider->getThreshold(SettingName::MAX_RAM);
	setTextBoxValue(metroTextBoxNET, (double)settings_provider->getThreshold(SettingName::MAX_NET) / 1000);
	setTextBoxValue(metroTextBoxHDD, (double)settings_provider->getThreshold(SettingName::MAX_HDD) / 1000);
	setTextBoxValue(metroTextBoxTimeMIN, Math::Floor(settings_provider->getThreshold(SettingName::WAIT_TIME) / 60));
	setTextBoxValue(metroTextBoxTimeSEC, settings_provider->getThreshold(SettingName::WAIT_TIME) - Math::Floor(settings_provider->getThreshold(SettingName::WAIT_TIME) / 60) * 60);
	metroToggleCPU->Checked = settings_provider->isActive(SettingName::USE_CPU);
	metroToggleHDD->Checked = settings_provider->isActive(SettingName::USE_HDD);
	metroToggleNET->Checked = settings_provider->isActive(SettingName::USE_NET);
	metroToggleRAM->Checked = settings_provider->isActive(SettingName::USE_RAM);
	metroToggleSOUND->Checked = settings_provider->isActive(SettingName::CHECK_SOUND);

	//Load AutoStart Setting
	metroToggleAutoStart->Checked = SystemAccess::IsInAutoStart();

	//Update UI
	metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
	metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);

	//ListView processes
	listViewProc->Font = BasicFunc::getMetroFont(9);

	//Load Processes
	refreshIcons();
	listViewProc->Items->Clear();
	for each(std::string str in  settings_provider->getProcessList()) {
		listViewProc->Items->Add(gcnew ProcessItem(str, listViewProc));
	}
	listViewProc->Update();

	//Presentation mode
	metroTogglePresMode->Checked = parent->isInPresentationMode();

	//Updates
	metroToggleUPDATES->Checked = settings_provider->isActive(SettingName::SEARCH_UPDATES);

	//Messages
	metroToggleMessages->Checked = settings_provider->isActive(SettingName::SHOW_MESSAGES);

	//Start Timer
	timerRefresh->Start();
	forceRefreshUI();

	switchLanguage();
}

double MetroSettingsForm::getTextBoxValueAsDouble(MetroFramework::Controls::MetroTextBox^ box) {
	box->Text = box->Text->Trim();
	box->Text = box->Text->Replace(".", ",");
	try {
		return Convert::ToDouble(box->Text);
	}
	catch (Exception^) {
		return -1;
	}
}

void MetroSettingsForm::setTextBoxValue(MetroFramework::Controls::MetroTextBox^ box, double value) {
	if (Math::Floor(value) == value) {
		//Number has no comma
		box->Text = String::Format("{0:00}", value);
	}
	else {
		box->Text = String::Format("{0:00.0}", value);
	}
}

void MetroSettingsForm::changeLabelBackgroundColor(MetroFramework::Controls::MetroLabel^ label, double SettingsValue, double readValue) {
	if (SettingsValue > readValue) {
		label->BackColor = lightGreen;
	}
	else {
		label->BackColor = lightRed;
	}
}

System::Void MetroSettingsForm::timerUIRefresh_Tick(System::Object^, System::EventArgs^) {
	float curCPU, curRAM, curHDD, curNET;
	//gets current system Usage
	curCPU = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::CPU);
	curRAM = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::RAM);
	curHDD = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::HDD);
	curNET = system_watcher->GetSystemMetric(SystemAccess::SystemMetric::NETWORK);

	//changes Background Color of the currentUsage Labels
	changeLabelBackgroundColor(metroLabelCurCPU, metroTrackBarCPU->Value, curCPU);
	changeLabelBackgroundColor(metroLabelCurRAM, metroTrackBarRAM->Value, curRAM);
	changeLabelBackgroundColor(metroLabelCurHDD, getTextBoxValueAsDouble(metroTextBoxHDD), curHDD / 1000);
	changeLabelBackgroundColor(metroLabelCurNET, getTextBoxValueAsDouble(metroTextBoxNET), curNET / 1000);

	//Formats Text on the currentUsage Labels
	metroLabelCurCPU->Text = String::Format("{0:00.00} %", curCPU);
	metroLabelCurHDD->Text = String::Format("{0:00.00} MBit/s", curHDD / 1000);
	metroLabelCurRAM->Text = String::Format("{0:00.00} % ", curRAM);
	metroLabelCurNET->Text = String::Format("{0:00.00} MBit/s", curNET / 1000);

	//Sets tool-tip to real-time usage and not the buffered one
	metroToolTip1->SetToolTip(metroLabelCurCPU, String::Format("Now: {0:00.00} %", system_access->GetMetric(SystemAccess::SystemMetric::CPU)));
	metroToolTip1->SetToolTip(metroLabelCurRAM, String::Format("Now: {0:00.00} % ", system_access->GetMetric(SystemAccess::SystemMetric::RAM)));
	metroToolTip1->SetToolTip(metroLabelCurHDD, String::Format("Now: {0:00.00} MBit/s", system_access->GetMetric(SystemAccess::SystemMetric::HDD) / 1000));
	metroToolTip1->SetToolTip(metroLabelCurNET, String::Format("Now: {0:00.00} MBit/s", system_access->GetMetric(SystemAccess::SystemMetric::NETWORK) / 1000));

	//this->Activate();
}
System::Void MetroSettingsForm::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	LOG("SettingsForm: OK Button Clicked");
	//disables Form;
	this->Visible = false;
	writeSettings();
	input_monitor->Reset();
	LOG("Settingsform closing");
}
System::Void MetroSettingsForm::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	LOG("SettingsForm: CANCEL Button Clicked");
	this->Visible = false;
	LOG("Settingsform closing");
}
System::Void MetroSettingsForm::metroButtonAddFromFile_Click(System::Object^, System::EventArgs^) {
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = "C:\\";
	ofd->Filter = "exe files(*.exe)|*.exe";
	ofd->FilterIndex = 1;
	ofd->RestoreDirectory = true;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if (ofd->CheckFileExists != false) {
			if (settings_provider->addProcessToProcessList(BasicFunc::StringToString(ofd->FileName))) {
				//If item is not already existing...
				listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ofd->FileName), listViewProc));
			}
			else {
				MessageBoxA(NULL, "Process has already been added!", "Error!", MB_OK);
			}
		}
	}
}
System::Void MetroSettingsForm::metroButtonAddFromList_Click(System::Object^, System::EventArgs^) {
	using namespace StandBye;
	ProcessSelectionForm^ ProcForm = gcnew ProcessSelectionForm;
	if (ProcForm->ShowDialog() == Windows::Forms::DialogResult::OK) {
		if (ProcForm->selectedProcessPath != "") {
			for each(ListViewItem^ item in listViewProc->Items) {
				ProcessItem^ p = (ProcessItem^)item;
				if (p->GetPath() == ProcForm->selectedProcessPath) {
					MessageBoxA(NULL, "Process has already been added!", "Error!", MB_OK);
					return;
				}
			}
			listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ProcForm->selectedProcessPath), listViewProc));
		}
	}
	delete ProcForm;
}
System::Void MetroSettingsForm::metroButtonRemove_Click(System::Object^, System::EventArgs^) {
	ProcessItem^ proc = (ProcessItem^)listViewProc->SelectedItems[0];
	settings_provider->removeProcessFromProcessList(BasicFunc::StringToString(proc->GetPath()));
	delete proc;
	refreshIcons();
}
System::Void MetroSettingsForm::listViewProc_SelectedIndexChanged(System::Object^, System::EventArgs^) {
	metroButtonRemove->Enabled = (listViewProc->SelectedItems->Count > 0);
}
System::Void MetroSettingsForm::metroToggleView_CheckedChanged(System::Object^, System::EventArgs^) {
	if (metroToggleView->Checked) {
		listViewProc->View = Windows::Forms::View::Details;
	}
	else {
		listViewProc->View = Windows::Forms::View::Tile;
	}
}

System::Void StandBye::MetroSettingsForm::metroToggleOnTop_CheckedChanged(System::Object ^, System::EventArgs ^)
{
	this->TopMost = metroToggleOnTop->Checked;
}

System::Void StandBye::MetroSettingsForm::metroTogglePresMode_CheckedChanged(System::Object ^, System::EventArgs ^)
{
	parent->setPresentationMode(metroTogglePresMode->Checked);
}

void MetroSettingsForm::refreshIcons() {
	ImageList^ imglistSmall = gcnew ImageList, ^imglistLarge = gcnew ImageList;

	imglistSmall->ImageSize = Drawing::Size(24, 24);
	imglistLarge->ImageSize = Drawing::Size(50, 50);

	listViewProc->SmallImageList = imglistSmall;
	listViewProc->LargeImageList = imglistLarge;

	for each(ProcessItem^ p in listViewProc->Items) {
		p->addIconToLists(listViewProc);
	}
}
System::Void MetroSettingsForm::metroTrackBarRAM_Scroll(System::Object^, System::Windows::Forms::ScrollEventArgs^) {
	if (metroLabelRAMPer->Text != String::Format("{0} %", metroTrackBarRAM->Value)) {
		metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);
	}
}
System::Void MetroSettingsForm::metroTrackBarCPU_Scroll(System::Object^, System::Windows::Forms::ScrollEventArgs^) {
	if (metroLabelCPUPer->Text != String::Format("{0} %", metroTrackBarCPU->Value)) {
		metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
	}
}
System::Void MetroSettingsForm::metroToggleAutoStart_CheckedChanged(System::Object^, System::EventArgs^) {
	SystemAccess::SetAutoStart(metroToggleAutoStart->Checked);
}
void StandBye::MetroSettingsForm::writeSettings()
{
	//Sets Settings
	settings_provider->setSetting(SettingName::MAX_CPU, Decimal::ToInt32(metroTrackBarCPU->Value));
	settings_provider->setSetting(SettingName::MAX_RAM, Decimal::ToInt32(metroTrackBarRAM->Value));
	settings_provider->setSetting(SettingName::MAX_HDD, (int)(getTextBoxValueAsDouble(metroTextBoxHDD) * 1000));
	settings_provider->setSetting(SettingName::MAX_NET, (int)(getTextBoxValueAsDouble(metroTextBoxNET) * 1000));
	settings_provider->setSetting(SettingName::WAIT_TIME, (int)getTextBoxValueAsDouble(metroTextBoxTimeMIN) * 60 + (int)getTextBoxValueAsDouble(metroTextBoxTimeSEC));
	settings_provider->setActiveState(SettingName::USE_CPU, metroToggleCPU->Checked);
	settings_provider->setActiveState(SettingName::USE_HDD, metroToggleHDD->Checked);
	settings_provider->setActiveState(SettingName::USE_RAM, metroToggleRAM->Checked);
	settings_provider->setActiveState(SettingName::USE_NET, metroToggleNET->Checked);
	settings_provider->setActiveState(SettingName::CHECK_SOUND, metroToggleSOUND->Checked);
	settings_provider->setActiveState(SettingName::SEARCH_UPDATES, metroToggleUPDATES->Checked);
	settings_provider->setActiveState(SettingName::SHOW_MESSAGES, metroToggleMessages->Checked);

	//Sets language
	settings_provider->setSetting(SettingName::LANGUAGE, BasicFunc::StringToString(CultureInfo::DefaultThreadCurrentCulture->TwoLetterISOLanguageName));

	//Sets processes
	for each(ListViewItem^ l in listViewProc->Items) {
		ProcessItem^ p = (ProcessItem^)l;
		p->Write(settings_provider);
	}

	//Writes settings to file
	if (!settings_provider->saveSettingsToFile()) {
		MessageBoxA(NULL, "Writing Settings not successful!", "Writing not successful!", MB_OK);
	}
}
System::Void MetroSettingsForm::metroTileHomepage_Click(System::Object^, System::EventArgs^) {
	ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::metroTileGithub_Click(System::Object^, System::EventArgs^) {
	ShellExecute(0, 0, "https://github.com/flobaader/Stand-Bye", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::metroLinkHomepage_Click(System::Object^, System::EventArgs^) {
	ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::ReformatTextBoxValueOnReturn(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e) {
	using MetroFramework::Controls::MetroTextBox;
	if (e->KeyCode == Windows::Forms::Keys::Return) {
		MetroTextBox^ txt = (MetroTextBox^)sender;
		double value = getTextBoxValueAsDouble(txt);
		if (value == -1) {
			//Could not convert
			txt->Text = "0.0";
			MessageBoxA(NULL, "Please insert numbers from 0 - 9", "Error!", MB_OK);
		}
		else {
			if (Math::Floor(value) == value) {
				//Number has no comma
				txt->Text = String::Format("{0:00}", value);
			}
			else {
				txt->Text = String::Format("{0:00.0}", value);
			}
		}
		forceRefreshUI();
		this->Activate();
	}
}

void MetroSettingsForm::forceRefreshUI() {
	timerUIRefresh_Tick(gcnew System::Object, gcnew System::EventArgs);
}

void StandBye::MetroSettingsForm::OnVisibleChanged(System::Object ^, System::EventArgs ^)
{
	if (this->Visible) {
		MetroSettingsForm_Load(nullptr, nullptr);
		timerRefresh->Start();
		forceRefreshUI();
	}
	else {
		timerRefresh->Stop();
	}
}

void StandBye::MetroSettingsForm::OnClosing(System::Object ^, System::ComponentModel::CancelEventArgs ^e)
{
	e->Cancel = true; //Form should not be closed, but only hidden
	this->Hide();
}

void StandBye::MetroSettingsForm::OnKeyDown(System::Object ^, System::Windows::Forms::KeyEventArgs ^e)
{
	if (e->Alt && e->Control && e->KeyCode == Windows::Forms::Keys::P) {
		metroTogglePresMode->Checked = !metroTogglePresMode->Checked;
	}
}

void StandBye::MetroSettingsForm::switchLanguage()
{
	CultureInfo^ cul = CultureInfo::DefaultThreadCurrentCulture;
	metroButtonOK->Text = res_man->GetString("ok", cul);
	metroButtonCancel->Text = res_man->GetString("cancel", cul);
	metroLabelTextWaitTime->Text = res_man->GetString("wait_time", cul);
	metroLabelTextSound->Text = res_man->GetString("cancel_on_sound", cul);
	metroLabelTextPresMode->Text = res_man->GetString("activate_pres_mode", cul);
	metroLabelTextCPU->Text = res_man->GetString("cpu_threshold", cul);
	metroLabelTextRAM->Text = res_man->GetString("ram_threshold", cul);
	metroLabelTextHDD->Text = res_man->GetString("hdd_threshold", cul);
	metroLabelTextNET->Text = res_man->GetString("net_threshold", cul);
	metroLabelTextAverageUsage->Text = res_man->GetString("avg_usage", cul);
	metroLabelTextProgramSettings->Text = res_man->GetString("program_settings", cul);
	metroLabelTextUsageThresholds->Text = res_man->GetString("system_usage_thresholds", cul);
	metroTabPageSettings->Text = res_man->GetString("settings", cul);
	metroTabPageExcpProcess->Text = res_man->GetString("excp_process", cul);
	metroTabPageAdvSettings->Text = res_man->GetString("adv_settings", cul);
	metroTabPageAbout->Text = res_man->GetString("about", cul);
	metroLabelTextExcpProcessExpl->Text = res_man->GetString("excp_process_text", cul);
	metroButtonAddFromFile->Text = res_man->GetString("add_process_file", cul);
	metroButtonAddFromList->Text = res_man->GetString("add_process_running", cul);
	metroLabelView->Text = res_man->GetString("show_details", cul);
	metroButtonRemove->Text = res_man->GetString("remove_process", cul);
	metroLabelTextAutoStart->Text = res_man->GetString("autostart", cul);
	metroLabelTextUpdates->Text = res_man->GetString("search_updates", cul);
	metroLabelTextMessages->Text = res_man->GetString("show_messages", cul);
	metroLabelTextOnTop->Text = res_man->GetString("alw_on_top", cul);
	metroLabelTextTutorial->Text = res_man->GetString("show_tutorial", cul);
	metroLabelTextLanguage->Text = res_man->GetString("language", cul);
	metroTileHomepage->Text = res_man->GetString("visit_homepage", cul);
	metroTileGithub->Text = res_man->GetString("visit_github", cul);
	metroLabelTextAbout->Text = res_man->GetString("about_text", cul);

	//Sets preferred Sizes
	for each(Windows::Forms::Control^ control in this->Controls) {
		control->Size = control->PreferredSize;
	}

	this->Update();
}

void StandBye::MetroSettingsForm::LanguageIndexChanged(System::Object ^, System::EventArgs ^)
{
	String^ selected_lang = metroComboBoxLanguage->Text;

	for each(CultureInfo^ supported_lang in supportedLanguages) {
		if (selected_lang == supported_lang->NativeName) {
			CultureInfo::DefaultThreadCurrentCulture = supported_lang;
			switchLanguage();
			parent->ReloadContextMenu();
			return;
		}
	}
	//Should not happen
	LOG("Selected language not supported: " + metroComboBoxLanguage->Text);
}