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

	//Loads Resource Manager
	res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
	res_manIMG = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);

	//Icons
	this->Icon = (System::Drawing::Icon^) res_manIMG->GetObject("icon1");
	infoGeneral->Icon = (System::Drawing::Image^) res_manIMG->GetObject("INFO");
	infoThresholds->Icon = (System::Drawing::Image^) res_manIMG->GetObject("INFO");

	//Sets version
	String^ versionText = gcnew String("v" + APP_VERSION);
	if ((bool)PORTABLE_VERSION) {
		versionText += " PORTABLE";
	}
	versionText += "\n" + "© Florian Baader, Stephan Le, Matthias Weirich";
	metroLabelVersion->Text = versionText;

	//Select Language
	metroComboBoxLanguage->Text = CultureInfo::DefaultThreadCurrentCulture->NativeName;
	switchLanguage();

	//Load Settings
	loadSettings();

	//Start Timer
	timerRefresh->Start();
	forceRefreshUI();

	//Activate
	this->Activate();
}

void StandBye::MetroSettingsForm::OnClosing(System::Object ^, System::ComponentModel::CancelEventArgs ^e)
{
	e->Cancel = true; //Form should not be closed, but only hidden
	this->Hide();
}

double StandBye::MetroSettingsForm::getTextAsDouble(String^ text) {
	text = text->Trim();
	text = text->Replace(".", ",");
	try {
		return Convert::ToDouble(text);
	}
	catch (Exception^) {
		return -1;
	}
}

String^ StandBye::MetroSettingsForm::FormatDigits(double value) {
	String^ formatter = "";

	for (int x = 1; x < 1000; x = x * 10) {
		if (value > x) {
			formatter += "0";
		}
	}

	if (!(Math::Floor(value) == value)) {
		//Number has comma
		formatter += ".0";
	}

	//Example String::Format("{0:00}", value)
	return String::Format("{0:" + formatter + "}", value);
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
	changeLabelBackgroundColor(metroLabelCurHDD, metroTrackBarHDD->Value, curHDD / 100);
	changeLabelBackgroundColor(metroLabelCurNET, metroTrackBarNET->Value, curNET / 100);

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
	settings_provider->setSetting(SettingName::MAX_HDD, Decimal::ToInt32(metroTrackBarHDD->Value) * 100);
	settings_provider->setSetting(SettingName::MAX_NET, Decimal::ToInt32(metroTrackBarNET->Value) * 100);
	settings_provider->setSetting(SettingName::WAIT_TIME, (int)getTextAsDouble(textBoxTimeMIN->Text) * 60 + (int)getTextAsDouble(textBoxTimeSEC->Text));
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
void StandBye::MetroSettingsForm::loadSettings()
{
	//Load Settings
	metroTrackBarCPU->Value = settings_provider->getThreshold(SettingName::MAX_CPU);
	metroTrackBarRAM->Value = settings_provider->getThreshold(SettingName::MAX_RAM);
	metroTrackBarHDD->Value = settings_provider->getThreshold(SettingName::MAX_HDD) / 100;
	metroTrackBarNET->Value = settings_provider->getThreshold(SettingName::MAX_NET) / 100;
	textBoxTimeMIN->Text = FormatDigits(Math::Floor(settings_provider->getThreshold(SettingName::WAIT_TIME) / 60));
	textBoxTimeSEC->Text = FormatDigits(settings_provider->getThreshold(SettingName::WAIT_TIME) - Math::Floor(settings_provider->getThreshold(SettingName::WAIT_TIME) / 60) * 60);
	metroToggleCPU->Checked = settings_provider->isActive(SettingName::USE_CPU);
	metroToggleHDD->Checked = settings_provider->isActive(SettingName::USE_HDD);
	metroToggleNET->Checked = settings_provider->isActive(SettingName::USE_NET);
	metroToggleRAM->Checked = settings_provider->isActive(SettingName::USE_RAM);
	metroToggleSOUND->Checked = settings_provider->isActive(SettingName::CHECK_SOUND);

	//Load AutoStart Setting
	metroToggleAutoStart->Checked = SystemAccess::IsInAutoStart();

	//Update UI
	metroTrackBarCPU_Scroll(nullptr, nullptr);
	metroTrackBarHDD_Scroll(nullptr, nullptr);
	metroTrackBarNET_Scroll(nullptr, nullptr);
	metroTrackBarRAM_Scroll(nullptr, nullptr);

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
	ShowPresModeStatus();

	//Updates
	metroToggleUPDATES->Checked = settings_provider->isActive(SettingName::SEARCH_UPDATES);

	//Messages
	metroToggleMessages->Checked = settings_provider->isActive(SettingName::SHOW_MESSAGES);
}
System::Void MetroSettingsForm::openGithubOnClick(System::Object^, System::EventArgs^) {
	BasicFunc::openLink("https://github.com/flobaader/Stand-Bye");
}
System::Void MetroSettingsForm::OpenHomepageOnClick(System::Object^, System::EventArgs^) {
	BasicFunc::openLink("http://www.stand-bye.de");
}
System::Void MetroSettingsForm::ReformatTextBoxValueOnReturn(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e) {
	using MetroFramework::Controls::MetroTextBox;
	if (e->KeyCode == Windows::Forms::Keys::Return) {
		Windows::Forms::TextBox^ txt = (Windows::Forms::TextBox^)sender;
		double value = getTextAsDouble(txt->Text);
		if (value == -1) {
			//Could not convert
			txt->Text = "0.0";
			MessageBoxA(NULL, "Please insert numbers from 0 - 9", "Error!", MB_OK);
		}
		else {
			txt->Text = FormatDigits(value);
		}
		forceRefreshUI();

		//Removes Focus
		txt->Enabled = false;
		txt->Enabled = true;
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
void StandBye::MetroSettingsForm::switchLanguage()
{
	//Culture
	CultureInfo^ cul = CultureInfo::DefaultThreadCurrentCulture;

	metroButtonOK->Text = res_man->GetString("ok", cul);
	metroButtonCancel->Text = res_man->GetString("cancel", cul);

	//Tab Pages
	metroTabPageSettings->Text = res_man->GetString("general", cul);
	metroTabPageExcpProcess->Text = res_man->GetString("excp_process", cul);
	metroTabPageAdvSettings->Text = res_man->GetString("adv_settings", cul);
	metroTabPageAbout->Text = res_man->GetString("about", cul);

	//General
	metroLabelTextWaitTime->Text = res_man->GetString("wait_time", cul);
	metroLabelTextSound->Text = res_man->GetString("cancel_on_sound", cul);
	metroTilePresMode->Text = res_man->GetString("activate_pres_mode", cul);

	//Thresholds
	metroLabelTextCPU->Text = res_man->GetString("cpu_threshold", cul);
	metroLabelTextRAM->Text = res_man->GetString("ram_threshold", cul);
	metroLabelTextHDD->Text = res_man->GetString("hdd_threshold", cul);
	metroLabelTextNET->Text = res_man->GetString("net_threshold", cul);
	metroLabelTextAverageUsage->Text = res_man->GetString("avg_usage", cul);

	metroButtonAddFromFile->Text = res_man->GetString("add_process_file", cul);
	metroButtonAddFromList->Text = res_man->GetString("add_process_running", cul);
	metroLabelView->Text = res_man->GetString("show_details", cul);
	metroButtonRemove->Text = res_man->GetString("remove_process", cul);
	metroLabelTextAutoStart->Text = res_man->GetString("autostart", cul);
	metroLabelTextUpdates->Text = res_man->GetString("search_updates", cul);
	metroLabelTextMessages->Text = res_man->GetString("show_messages", cul);
	metroLabelTextLanguage->Text = res_man->GetString("language", cul);
	metroTileHomepage->Text = res_man->GetString("visit_homepage", cul);
	metroTileGithub->Text = res_man->GetString("visit_github", cul);
	metroLabelTextAbout->Text = res_man->GetString("about_text", cul);
	metroTabPageThresholds->Text = res_man->GetString("thresholds", cul);

	//Info
	if (true)
	{
		infoExcpProcesses->Text = res_man->GetString("info_excp", cul);
		infoThresholds->Text = res_man->GetString("info_thresholds", cul);
		infoGeneral->Text = res_man->GetString("info_general", cul);

		//Explanations

		explCPU->Text = res_man->GetString("expl_CPU", cul);
		explRAM->Text = res_man->GetString("expl_RAM", cul);
		explHDD->Text = res_man->GetString("expl_HDD", cul);
		explNET->Text = res_man->GetString("expl_NET", cul);
	}
	else {
		infoExcpProcesses->Text = "";
		infoThresholds->Text = "";
		infoGeneral->Text = "";
	}

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

System::Void StandBye::MetroSettingsForm::metroTilePresMode_Click(System::Object^, System::EventArgs^)
{
	ShowPresModeStatus();
	parent->setPresentationMode(!parent->isInPresentationMode());
}

void StandBye::MetroSettingsForm::ShowPresModeStatus()
{
	if (parent->isInPresentationMode()) {
		metroTilePresMode->TileImage = (System::Drawing::Image^) res_manIMG->GetObject("CHECKED");
	}
	else {
		metroTilePresMode->TileImage = (System::Drawing::Image^) res_manIMG->GetObject("CROSS");
	}
	metroTilePresMode->Update();
}

void StandBye::MetroSettingsForm::OnMetroTileMouseEnter(System::Object ^sender, System::EventArgs ^)
{
	using MetroFramework::Controls::MetroTile;

	MetroTile^ tile = (MetroTile^)sender;
	//tile->Size = System::Drawing::Size(tile->Size.Height - 1, tile->Size.Width - 1);
	tile->UseCustomBackColor = true;
	tile->BackColor = Color::LightGray;
	//tile->Margin = Windows::Forms::Padding(5);
	tile->Update();
}

void StandBye::MetroSettingsForm::OnMetroTileMouseLeave(System::Object ^sender, System::EventArgs ^)
{
	using MetroFramework::Controls::MetroTile;

	MetroTile^ tile = (MetroTile^)sender;
	//tile->Size = System::Drawing::Size(tile->Size.Height + 1, tile->Size.Width + 1);
	//tile->Margin = Windows::Forms::Padding(5);
	tile->UseCustomBackColor = false;
	tile->Update();
}

void StandBye::MetroSettingsForm::OnTextBoxMouseEnter(System::Object ^sender, System::EventArgs ^)
{
	Windows::Forms::TextBox^ box = (TextBox^)sender;
	box->BackColor = Color::LightGray;
	box->Update();
}

void StandBye::MetroSettingsForm::OnTextBoxMouseLeave(System::Object ^sender, System::EventArgs ^)
{
	Windows::Forms::TextBox^ box = (TextBox^)sender;
	box->BackColor = box->Parent->BackColor;
	box->Update();
}

System::Void StandBye::MetroSettingsForm::metroTileAbout_Click(System::Object^, System::EventArgs^)
{
	metroTabControl1->SelectedTab = metroTabPageAbout;
}

System::Void StandBye::MetroSettingsForm::metroTileProcesses_Click(System::Object^, System::EventArgs^)
{
	metroTabControl1->SelectedTab = metroTabPageExcpProcess;
}

System::Void StandBye::MetroSettingsForm::metroTileSettings_Click(System::Object^, System::EventArgs^)
{
	metroTabControl1->SelectedTab = metroTabPageThresholds;
}

System::Void StandBye::MetroSettingsForm::metroTrackBarHDD_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
{
	if (metroLabelHDDStatus->Text != String::Format("{0:0.0} MBit/s", (double)metroTrackBarHDD->Value / 10)) {
		metroLabelHDDStatus->Text = String::Format("{0:0.0} MBit/s", (double)metroTrackBarHDD->Value / 10);
	}
}

System::Void StandBye::MetroSettingsForm::metroTrackBarNET_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
{
	if (metroLabelNETStatus->Text != String::Format("{0:0.0} MBit/s", (double)metroTrackBarNET->Value / 10)) {
		metroLabelNETStatus->Text = String::Format("{0:0.0} MBit/s", (double)metroTrackBarNET->Value / 10);
	}
}