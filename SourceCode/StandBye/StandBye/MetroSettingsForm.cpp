//////////////////////////////////////////////////////////////////////////
/*!
 * STAND-BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de or https://github.com/flobaader/Stand-Bye
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MetroSettingsForm.h"
#include "mainApplication.h"
using namespace StandBye;
void StandBye::MetroSettingsForm::PrepareForm()
{
	//Focus on first tabPage
	metroTabControlMain->SelectedTab = metroTabPageGeneral;

	//Sets Events
	registerEvents();

	//Loads Resource Manager
	res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
	res_manIMG = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);

	//Icons
	this->Icon = (System::Drawing::Icon^) res_manIMG->GetObject("icon1");
	infoGeneral->Icon = (System::Drawing::Image^) res_manIMG->GetObject("INFO");
	infoThresholds->Icon = (System::Drawing::Image^) res_manIMG->GetObject("INFO");

	//Sets version
	String^ versionText = gcnew String("v" + APP_VERSION);
	if (SystemAccess::isPortable()) {
		versionText += " PORTABLE";
	}
	versionText += "\n" + L"(c) Florian Baader, Stephan Le, Matthias Weirich";
	metroLabelVersion->Text = versionText;

	//Sets languages
	metroComboBoxLanguage->Items->Clear();
	for each(CultureInfo^ cul in supportedLanguages) {
		metroComboBoxLanguage->Items->Add(cul->NativeName);
	}

	//Sets dateTime Font
	dateTimePickerStandbyStart->Font = BasicFunc::getMetroFont(12);

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

void StandBye::MetroSettingsForm::cleanResources()
{
	delete system_access;
	system_watcher->Stop();
	delete system_watcher;
	res_man->ReleaseAllResources();
	delete res_man;
	res_manIMG->ReleaseAllResources();
	delete res_manIMG;
}

void StandBye::MetroSettingsForm::registerEvents()
{
	//Main
	this->metroButtonOK->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonOK_Click);
	this->metroButtonCancel->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonCancel_Click);
	this->metroLinkHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::OpenHomepageOnClick);
	this->timerRefresh->Tick += gcnew System::EventHandler(this, &MetroSettingsForm::timerUIRefresh_Tick);

	//General
	metroTilePresMode->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTilePresMode->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileAbout->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileAbout->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileVisit->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileVisit->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileProcesses->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileProcesses->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileSettings->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileSettings->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);

	textBoxTimeMIN->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnTextBoxMouseEnter);
	textBoxTimeMIN->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnTextBoxMouseLeave);
	textBoxTimeSEC->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnTextBoxMouseEnter);
	textBoxTimeSEC->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnTextBoxMouseLeave);

	textBoxTimeMIN->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &StandBye::MetroSettingsForm::ReformatTextBoxValueOnReturn);
	textBoxTimeSEC->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &StandBye::MetroSettingsForm::ReformatTextBoxValueOnReturn);

	metroTileAbout->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::metroTileAbout_Click);
	metroTileProcesses->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::metroTileProcesses_Click);
	metroTileSettings->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::metroTileSettings_Click);
	metroTilePresMode->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::metroTilePresMode_Click);
	metroTileVisit->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OpenHomepageOnClick);

	//Thresholds
	this->metroTrackBarCPU->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarCPU_Scroll);
	this->metroTrackBarRAM->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarRAM_Scroll);
	this->metroTrackBarHDD->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarHDD_Scroll);
	this->metroTrackBarNET->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MetroSettingsForm::metroTrackBarNET_Scroll);

	//Processes
	this->listViewProc->SelectedIndexChanged += gcnew System::EventHandler(this, &MetroSettingsForm::listViewProc_SelectedIndexChanged);
	this->metroButtonRemove->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonRemove_Click);
	this->metroButtonAddFromList->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonAddFromList_Click);
	this->metroButtonAddFromFile->Click += gcnew System::EventHandler(this, &MetroSettingsForm::metroButtonAddFromFile_Click);
	this->metroToggleView->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleView_CheckedChanged);

	//Advanced
	this->metroToggleAutoStart->CheckedChanged += gcnew System::EventHandler(this, &MetroSettingsForm::metroToggleAutoStart_CheckedChanged);
	this->metroComboBoxLanguage->SelectedIndexChanged += gcnew System::EventHandler(this, &MetroSettingsForm::LanguageIndexChanged);

	//About
	metroTileHomepage->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileHomepage->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileGithub->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileGithub->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);
	metroTileDonate->MouseEnter += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseEnter);
	metroTileDonate->MouseLeave += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OnMetroTileMouseLeave);

	this->metroTileHomepage->Click += gcnew System::EventHandler(this, &MetroSettingsForm::OpenHomepageOnClick);
	this->metroTileGithub->Click += gcnew System::EventHandler(this, &MetroSettingsForm::openGithubOnClick);
	this->metroTileDonate->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OpenHomepageOnClick);
	this->metroLinkContact->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::ContactLink);
	this->textBoxLicense->Click += gcnew System::EventHandler(this, &StandBye::MetroSettingsForm::OpenLicense);
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

void MetroSettingsForm::changeLabelBackgroundColor(MetroFramework::Controls::MetroLabel^ label, double setValue, double realTimeValue, bool isActive) {
	if (setValue > realTimeValue && isActive) {
		label->BackColor = lightGreen;
	}
	else if(isActive){
		label->BackColor = lightRed;
	}
	else {
		label->BackColor = Color::LightGray;
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
	changeLabelBackgroundColor(metroLabelCurCPU, metroTrackBarCPU->Value, curCPU, metroToggleCPU->Checked);
	changeLabelBackgroundColor(metroLabelCurRAM, metroTrackBarRAM->Value, curRAM, metroToggleRAM->Checked);
	changeLabelBackgroundColor(metroLabelCurHDD, metroTrackBarHDD->Value, curHDD / 100, metroToggleHDD->Checked);
	changeLabelBackgroundColor(metroLabelCurNET, metroTrackBarNET->Value, curNET / 100, metroToggleNET->Checked);

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

	//Sets icon of status tile
	if (parent->isSystemBusy(system_watcher)) {
		this->metroTileCanceledStatus->TileImage = (System::Drawing::Image^) res_manIMG->GetObject("CIRCLE_UNCHECKED");
		this->metroTileCanceledStatus->Text = res_man->GetString("standby_canceled", CultureInfo::DefaultThreadCurrentCulture);
	}
	else {
		this->metroTileCanceledStatus->TileImage = (System::Drawing::Image^) res_manIMG->GetObject("CIRCLE_CHECKED");
		this->metroTileCanceledStatus->Text = res_man->GetString("standby_activated", CultureInfo::DefaultThreadCurrentCulture);
	}

	//Update
	this->Update();
}
System::Void MetroSettingsForm::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	//Check Limits
	//Checks if Wait-Time is over the limit
	if (!isWaitTimeOverMin()) {
		return;
	}
	
	LOG("SettingsForm: OK Button Clicked");
	//disables Form;
	this->Visible = false;
	writeSettings();
	this->Close();
}
System::Void MetroSettingsForm::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	LOG("SettingsForm: CANCEL Button Clicked");
	this->Close();
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
				//The process has already been added
				String^ msg = res_man->GetString("msg_processAlreadyAdded", CultureInfo::DefaultThreadCurrentCulture);
				MessageWindow^ msgWin = gcnew MessageWindow(msg, Windows::Forms::MessageBoxButtons::OK);
				msgWin->ShowDialog();
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
	settings_provider->setActiveState(SettingName::LOGGING, metroToggleLogging->Checked);
	settings_provider->setActiveState(SettingName::USE_SLEEPTIME, metroToggleSleepTime->Checked);
	settings_provider->setSetting(SettingName::SLEEPTIME, BasicFunc::StringToString(dateTimePickerStandbyStart->Value.ToString("HH:mm")));

	//Sets language
	settings_provider->setSetting(SettingName::LANGUAGE, BasicFunc::StringToString(CultureInfo::DefaultThreadCurrentCulture->TwoLetterISOLanguageName));

	//Sets processes
	for each(ListViewItem^ l in listViewProc->Items) {
		ProcessItem^ p = (ProcessItem^)l;
		p->Write(settings_provider);
	}

	//Standby mode
	if (metroComboBoxStandby->Text == res_man->GetString("suspend", CultureInfo::DefaultThreadCurrentCulture)) {
		settings_provider->setSetting(SettingName::STANDBY_MODE, "SUSPEND");
	}
	else {
		settings_provider->setSetting(SettingName::STANDBY_MODE, "HIBERNATE");
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
	metroToggleLogging->Checked = settings_provider->isActive(SettingName::LOGGING);
	metroToggleSleepTime->Checked = settings_provider->isActive(SettingName::USE_SLEEPTIME);
	dateTimePickerStandbyStart->Value = DateTime::ParseExact(gcnew String(settings_provider->getRawSetting(SettingName::SLEEPTIME).c_str()),
		gcnew String("HH:mm"), CultureInfo::CreateSpecificCulture("de"));

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

	//Standby mode
	if (settings_provider->getRawSetting(SettingName::STANDBY_MODE) == "SUSPEND") {
		metroComboBoxStandby->Text = res_man->GetString("suspend", CultureInfo::DefaultThreadCurrentCulture);
	}
	else {
		metroComboBoxStandby->Text = res_man->GetString("hibernate", CultureInfo::DefaultThreadCurrentCulture);
	}

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
	BasicFunc::openLink("http://www.stand-bye.de/feedback");
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
	timerUIRefresh_Tick(nullptr, nullptr);
}
void StandBye::MetroSettingsForm::switchLanguage()
{
	//Culture
	CultureInfo^ cul = CultureInfo::DefaultThreadCurrentCulture;

	metroButtonOK->Text = res_man->GetString("save", cul);
	metroButtonCancel->Text = res_man->GetString("cancel", cul);

	//Tab Pages
	metroTabPageGeneral->Text = res_man->GetString("general", cul);
	metroTabPageExcpProcess->Text = res_man->GetString("excp_process", cul);
	metroTabPageAdvSettings->Text = res_man->GetString("adv_settings", cul);
	metroTabPageAbout->Text = res_man->GetString("about", cul);
	metroTabPageThresholds->Text = res_man->GetString("thresholds", cul);

	//General
	metroLabelTextWaitTime->Text = res_man->GetString("wait_time", cul);
	metroLabelTextSound->Text = res_man->GetString("cancel_on_sound", cul);
	metroTilePresMode->Text = res_man->GetString("activate_pres_mode", cul);
	metroTileAbout->Text = res_man->GetString("about", cul);
	metroTileVisit->Text = res_man->GetString("visit_us", cul);
	metroTileProcesses->Text = res_man->GetString("processes", cul);
	metroTileSettings->Text = res_man->GetString("settings", cul);

	//Thresholds
	metroLabelTextCPU->Text = res_man->GetString("cpu_threshold", cul);
	metroLabelTextRAM->Text = res_man->GetString("ram_threshold", cul);
	metroLabelTextHDD->Text = res_man->GetString("hdd_threshold", cul);
	metroLabelTextNET->Text = res_man->GetString("net_threshold", cul);
	metroLabelTextAverageUsage->Text = res_man->GetString("avg_usage", cul);
	metroLabelTextStartStandBy->Text = res_man->GetString("start_standby_at", cul);
	explStartStandbyAt->Text = res_man->GetString("expl_StandbyAt", cul);
	explSOUND->Text = res_man->GetString("expl_SOUND", cul);
	groupBoxFeatures->Text = res_man->GetString("feature", cul);
	groupBoxThresholds->Text = res_man->GetString("general_thresholds", cul);

	//Processes
	metroButtonAddFromFile->Text = res_man->GetString("add_process_file", cul);
	metroButtonAddFromList->Text = res_man->GetString("add_process_running", cul);
	metroLabelView->Text = res_man->GetString("show_details", cul);
	metroButtonRemove->Text = res_man->GetString("remove_process", cul);

	//Advanced Settings
	metroLabelTextAutoStart->Text = res_man->GetString("autostart", cul);
	metroLabelTextUpdates->Text = res_man->GetString("search_updates", cul);
	metroLabelTextMessages->Text = res_man->GetString("show_messages", cul);
	metroLabelTextLanguage->Text = res_man->GetString("language", cul);
	metroLabelTextLogging->Text = res_man->GetString("enable_log", cul);
	metroLabelTextSelectStandby->Text = res_man->GetString("select_standby", cul);
	metroLabelGeneralSettings->Text = res_man->GetString("general_settings", cul);
	metroLabelStandbyeSettings->Text = res_man->GetString("standbye_settings", cul);

	//About
	metroTileHomepage->Text = res_man->GetString("visit_homepage", cul);
	metroTileGithub->Text = res_man->GetString("visit_github", cul);
	metroTileDonate->Text = res_man->GetString("donate", cul);
	metroLabelSupport->Text = res_man->GetString("support_us", cul);
	metroLabelLicenseHeading->Text = res_man->GetString("license_heading", cul);
	metroLinkContact->Text = res_man->GetString("contact", cul);

	//Info
	infoExcpProcesses->Text = res_man->GetString("info_excp", cul);
	infoThresholds->Text = res_man->GetString("info_thresholds", cul);
	infoGeneral->Text = res_man->GetString("info_general", cul);

	//Explanations
	explCPU->Text = res_man->GetString("expl_CPU", cul);
	explRAM->Text = res_man->GetString("expl_RAM", cul);
	explHDD->Text = res_man->GetString("expl_HDD", cul);
	explNET->Text = res_man->GetString("expl_NET", cul);
	explSOUND->Text = res_man->GetString("expl_SOUND", cul);

	//Standby modes
	metroComboBoxStandby->Items->Clear();
	metroComboBoxStandby->Items->Add(res_man->GetString("suspend", cul));
	metroComboBoxStandby->Items->Add(res_man->GetString("hibernate", cul));

	//Sets preferred Sizes
	for each(Windows::Forms::Control^ control in this->Controls) {
		control->Size = control->PreferredSize;
		control->PerformLayout();
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
	parent->setPresentationMode(!parent->isInPresentationMode());
	//Change Label of Tile
	ShowPresModeStatus();
	//Ensures that the canceled status is updated
	forceRefreshUI();
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
	tile->UseCustomBackColor = true;
	tile->BackColor = Color::LightGray;
	tile->Cursor = Cursors::Hand;
	tile->Update();
}

void StandBye::MetroSettingsForm::OnMetroTileMouseLeave(System::Object ^sender, System::EventArgs ^)
{
	using MetroFramework::Controls::MetroTile;

	MetroTile^ tile = (MetroTile^)sender;
	tile->UseCustomBackColor = false;
	tile->Update();
}

void StandBye::MetroSettingsForm::OnTextBoxMouseEnter(System::Object ^sender, System::EventArgs ^)
{
	Windows::Forms::TextBox^ box = (TextBox^)sender;
	box->BackColor = Color::LightGray;
	box->Cursor = Cursors::IBeam;
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
	metroTabControlMain->SelectedTab = metroTabPageAbout;
}

System::Void StandBye::MetroSettingsForm::metroTileProcesses_Click(System::Object^, System::EventArgs^)
{
	metroTabControlMain->SelectedTab = metroTabPageExcpProcess;
}

System::Void StandBye::MetroSettingsForm::metroTileSettings_Click(System::Object^, System::EventArgs^)
{
	metroTabControlMain->SelectedTab = metroTabPageThresholds;
}

bool StandBye::MetroSettingsForm::isWaitTimeOverMin()
{
	int seconds = (int) getTextAsDouble(textBoxTimeMIN->Text) * 60 + (int) getTextAsDouble(textBoxTimeSEC->Text);
	if (seconds < 15) {
		// The Wait-Time should not be under 15 seconds
		MessageWindow^ msgW = gcnew MessageWindow(res_man->GetString("msg_waitTimeMinWarning"), System::Windows::Forms::MessageBoxButtons::OK);
		msgW->Show();
		textBoxTimeMIN->Text = "1";
		textBoxTimeSEC->Text = "0";
		return false;
	}
	return true;
}

System::Void StandBye::MetroSettingsForm::metroTrackBarHDD_Scroll(System::Object^, System::Windows::Forms::ScrollEventArgs^)
{
	if (metroLabelHDDStatus->Text != String::Format("{0:0.0} MBit/s", (double)metroTrackBarHDD->Value / 10)) {
		metroLabelHDDStatus->Text = String::Format("{0:0.0} MBit/s", (double)metroTrackBarHDD->Value / 10);
	}
}

System::Void StandBye::MetroSettingsForm::metroTrackBarNET_Scroll(System::Object^, System::Windows::Forms::ScrollEventArgs^)
{
	if (metroLabelNETStatus->Text != String::Format("{0:0.00} MBit/s", (double)metroTrackBarNET->Value / 200)) {
		metroLabelNETStatus->Text = String::Format("{0:0.00} MBit/s", (double)metroTrackBarNET->Value / 200);
	}
}

void StandBye::MetroSettingsForm::ContactLink(System::Object ^, System::EventArgs ^)
{
	BasicFunc::openLink("mailto:contact@stand-bye.de");
}

void StandBye::MetroSettingsForm::OpenLicense(System::Object ^, System::EventArgs ^)
{
	BasicFunc::openLink("http://stand-bye.de/html/license.txt");
}