#include "stdafx.h"
#include "MetroSettingsForm.h"
using namespace StandBye;

void MetroSettingsForm::forceRefreshUI() {
	timerUIRefresh_Tick(gcnew System::Object, gcnew System::EventArgs);
}
System::Void MetroSettingsForm::MetroSettingsForm_Load(System::Object^  sender, System::EventArgs^  e) {
	//Focus on first tabPage
	metroTabControl1->SelectedTab = metroTabPage1;

	//Load Settings
	metroTrackBarCPU->Value = settings_provider->getThreshold(SettingName::MAX_CPU);
	metroTrackBarRAM->Value = settings_provider->getThreshold(SettingName::MAX_RAM);
	setTextBoxValue(metroTextBoxNET, (double)settings_provider->getThreshold(SettingName::MAX_NET) / 1000);
	setTextBoxValue(metroTextBoxHDD, (double)settings_provider->getThreshold(SettingName::MAX_HDD) / 1000);
	setTextBoxValue(metroTextBoxWAITTIME, settings_provider->getThreshold(SettingName::WAIT_TIME) / 60);
	metroToggleCPU->Checked = settings_provider->isActive(SettingName::USE_CPU);
	metroToggleHDD->Checked = settings_provider->isActive(SettingName::USE_HDD);
	metroToggleNET->Checked = settings_provider->isActive(SettingName::USE_NET);
	metroToggleRAM->Checked = settings_provider->isActive(SettingName::USE_RAM);

	//Load AutoStart Setting
	metroToggleAutoStart->Checked = SystemAccess::IsInAutoStart();

	//Update UI
	metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
	metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);

	//ListView processes
	listViewProc->Font = BasicFunc::getMetroFont(9);

	//Load Processes
	refreshIcons();
	for each(std::string str in  settings_provider->getProcessList()) {
		listViewProc->Items->Add(gcnew ProcessItem(str, listViewProc));
	}
	listViewProc->Update();

	//Start Timer
	timerRefresh->Start();
	forceRefreshUI();
}
bool MetroSettingsForm::isNumber(std::string line) {
	char* p;
	strtol(line.c_str(), &p, 10);
	return *p == 0;
}

double MetroSettingsForm::getTextBoxValueAsDouble(MetroFramework::Controls::MetroTextBox^ box) {
	box->Text = box->Text->Replace(",", ".");
	double value = -1;
	value = atof(BasicFunc::StringToString(box->Text).c_str());
	return value;
}

void MetroSettingsForm::setTextBoxValue(MetroFramework::Controls::MetroTextBox^ box, double value) {
	box->Text = String::Format("{0:00.0}", value);
}

System::Void MetroSettingsForm::metroTextBoxWAITTIME_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (isNumber(BasicFunc::StringToString(metroTextBoxWAITTIME->Text)) == false) {
		metroTextBoxWAITTIME->Text = "";
	}
	forceRefreshUI();
}
void MetroSettingsForm::changeLabelBackgroundColor(MetroFramework::Controls::MetroLabel^ label, double SettingsValue, double readValue) {
	if (SettingsValue > readValue) {
		label->BackColor = lightGreen;
	}
	else {
		label->BackColor = lightRed;
	}
}

System::Void MetroSettingsForm::timerUIRefresh_Tick(System::Object^  sender, System::EventArgs^  e) {
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
}
System::Void MetroSettingsForm::metroButtonOK_Click(System::Object^  sender, System::EventArgs^  e) {
	settings_provider->setSetting(SettingName::MAX_CPU, Decimal::ToInt32(metroTrackBarCPU->Value));
	settings_provider->setSetting(SettingName::MAX_RAM, Decimal::ToInt32(metroTrackBarRAM->Value));
	settings_provider->setSetting(SettingName::MAX_HDD, (int)(getTextBoxValueAsDouble(metroTextBoxHDD) * 1000));
	settings_provider->setSetting(SettingName::MAX_NET, (int)(getTextBoxValueAsDouble(metroTextBoxNET) * 1000));
	settings_provider->setSetting(SettingName::WAIT_TIME, getTextBoxValueAsDouble(metroTextBoxWAITTIME) * 60);
	settings_provider->setActiveState(SettingName::USE_CPU, metroToggleCPU->Checked);
	settings_provider->setActiveState(SettingName::USE_HDD, metroToggleHDD->Checked);
	settings_provider->setActiveState(SettingName::USE_RAM, metroToggleRAM->Checked);
	settings_provider->setActiveState(SettingName::USE_NET, metroToggleNET->Checked);

	for each(ListViewItem^ l in listViewProc->Items) {
		ProcessItem^ p = (ProcessItem^)l;
		p->Write(settings_provider);
	}

	if (settings_provider->saveSettingsToFile() == false) {
		MessageBoxA(NULL, "Writing Settings not successful!", "Writing not successful!", MB_OK);
	}
	this->DialogResult = Windows::Forms::DialogResult::OK;
	this->Hide();
}
System::Void MetroSettingsForm::metroButtonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Hide();
}
System::Void MetroSettingsForm::metroButtonAddFromFile_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->InitialDirectory = "C:\\";
	ofd->Filter = "exe files(*.exe)|*.exe";
	ofd->FilterIndex = 1;
	ofd->RestoreDirectory = true;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		if (ofd->CheckFileExists != false) {
			settings_provider->addProcessToProcessList(BasicFunc::StringToString(ofd->FileName));
			listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ofd->FileName), listViewProc));
		}
	}
}
System::Void MetroSettingsForm::metroButtonAddFromList_Click(System::Object^  sender, System::EventArgs^  e) {
	using namespace StandBye;
	ProcessSelectionForm^ ProcForm = gcnew ProcessSelectionForm;
	if (ProcForm->ShowDialog() == Windows::Forms::DialogResult::OK) {
		if (ProcForm->selectedProcessPath != "") {
			listViewProc->Items->Add(gcnew ProcessItem(BasicFunc::StringToString(ProcForm->selectedProcessPath), listViewProc));
		}
	}
	delete ProcForm;
}
System::Void MetroSettingsForm::metroButtonRemove_Click(System::Object^  sender, System::EventArgs^  e) {
	ProcessItem^ proc = (ProcessItem^)listViewProc->SelectedItems[0];
	settings_provider->removeProcessFromProcessList(BasicFunc::StringToString(proc->GetPath()));
	delete proc;
	refreshIcons();
}
System::Void MetroSettingsForm::listViewProc_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	metroButtonRemove->Enabled = (listViewProc->SelectedItems->Count > 0);
}
System::Void MetroSettingsForm::metroToggleView_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
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
System::Void MetroSettingsForm::metroTrackBarRAM_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
	metroLabelRAMPer->Text = String::Format("{0} %", metroTrackBarRAM->Value);
}
System::Void MetroSettingsForm::metroTrackBarCPU_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
	metroLabelCPUPer->Text = String::Format("{0} %", metroTrackBarCPU->Value);
}
System::Void MetroSettingsForm::metroToggleAutoStart_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	SystemAccess::SetAutoStart(metroToggleAutoStart->Checked);
}
System::Void MetroSettingsForm::metroTileHomepage_Click(System::Object^  sender, System::EventArgs^  e) {
	ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::metroTileGithub_Click(System::Object^  sender, System::EventArgs^  e) {
	ShellExecute(0, 0, "https://github.com/flobaader/Stand-Bye", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::metroLinkHomepage_Click(System::Object^  sender, System::EventArgs^  e) {
	ShellExecute(0, 0, "http://www.stand-bye.de", 0, 0, SW_SHOW);
}
System::Void MetroSettingsForm::ReformatTextBoxValueOnReturn(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e) {
	using MetroFramework::Controls::MetroTextBox;
	if (e->KeyCode == Windows::Forms::Keys::Return) {
		MetroTextBox^ txt = (MetroTextBox^)sender;
		if (getTextBoxValueAsDouble(txt) == -1) {
			txt->Text = "";
		}
		else {
			txt->Text = String::Format("{0:00.0}", getTextBoxValueAsDouble(txt));
		}
		forceRefreshUI();
	}
}