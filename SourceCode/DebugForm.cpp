//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: DebugForm.cpp
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DebugForm.h"
using namespace StandBye;

System::Void StandBye::DebugForm::DebugForm_Load(System::Object ^, System::EventArgs ^)
{
	RefreshUISlow();
}

System::Void StandBye::DebugForm::buttonSettingsForm_Click(System::Object ^, System::EventArgs ^)
{
	parent->OpenSettingsForm();
}

System::Void StandBye::DebugForm::buttonProcessForm_Click(System::Object ^, System::EventArgs ^)
{
	ProcessSelectionForm^ form = gcnew ProcessSelectionForm();
	form->ShowDialog();
}

System::Void StandBye::DebugForm::buttonMessageWnd_Click(System::Object ^, System::EventArgs ^)
{
	MessageWindow^ wnd = gcnew MessageWindow("This is a test");
	wnd->ShowDialog();
}

System::Void StandBye::DebugForm::buttonTimeWnd_Click(System::Object ^, System::EventArgs ^)
{
	TimeoutWindow^ wnd = gcnew TimeoutWindow(15, settings_prov);
	wnd->ShowDialog();
}

System::String ^ StandBye::DebugForm::getLogText()
{
	using namespace System;
	using namespace System::IO;

	String^ return_string = "";
	StreamReader^ sr;

	try {
		sr = gcnew StreamReader(BasicFunc::getLogFilePath());
		while (sr->Peek() >= 0) {
			return_string += sr->ReadLine() + "\n";
		}
	}
	catch (System::IO::IOException^) {
		//File is opened from an other process
		return "";
	}
	finally{
		delete sr;
	}

	return return_string;
}

void DebugForm::OnTick(System::Object ^, System::EventArgs ^)
{
	RefreshUIRealTime();
}

void DebugForm::RefreshUISlow()
{
	//ListView Settings
	for each(Setting* setting in settings_prov->getAllSettings()) {
		String^ name = gcnew String(setting->GetNameAsString().c_str());
		string std_value;

		//Adds all values to an single String^
		for each(string single_value in setting->GetValue()) {
			std_value += single_value;
		}
		String^ value = gcnew String(std_value.c_str());

		listViewSettings->Items->Add(name)->SubItems->Add(value);
	}

	//ListView Processes
	//Prepare ListView
	listViewProc->View = Windows::Forms::View::Details;
	ImageList^ imglistSmall = gcnew ImageList, ^imglistLarge = gcnew ImageList;
	imglistSmall->ImageSize = Drawing::Size(24, 24);
	imglistLarge->ImageSize = Drawing::Size(50, 50);
	listViewProc->SmallImageList = imglistSmall;
	listViewProc->LargeImageList = imglistLarge;

	for each(std::string path in SystemAccess::GetRunningProccesses()) {
		listViewProc->Items->Add(gcnew ProcessItem(path, listViewProc));
	}
}

void StandBye::DebugForm::RefreshUIRealTime()
{
	//Buffered Values
	labelBuffCPU->Text = String::Format("{0:00.0} %", system_watcher->GetSystemMetric(SystemAccess::SystemMetric::CPU));
	labelBuffRAM->Text = String::Format("{0:00.0} %", system_watcher->GetSystemMetric(SystemAccess::SystemMetric::RAM));
	labelBuffHDD->Text = String::Format("{0:00.0} kBit/s", system_watcher->GetSystemMetric(SystemAccess::SystemMetric::HDD));
	labelBuffNET->Text = String::Format("{0:00.0} kBit/s", system_watcher->GetSystemMetric(SystemAccess::SystemMetric::NETWORK));

	//Real-Time Values
	labelRTCPU->Text = String::Format("{0:00.0} %", system_access->GetMetric(SystemAccess::SystemMetric::CPU));
	labelRTRAM->Text = String::Format("{0:00.0} %", system_access->GetMetric(SystemAccess::SystemMetric::RAM));
	labelRTHDD->Text = String::Format("{0:00.0} kBit/s", system_access->GetMetric(SystemAccess::SystemMetric::HDD));
	labelRTNET->Text = String::Format("{0:00.0} kBit/s", system_access->GetMetric(SystemAccess::SystemMetric::NETWORK));

	//Input Info
	int lastinput = (int)system_access->GetLastInputTime();
	labelInputTime->Text = String::Format("{0} ms", lastinput);

	if ((lastinput / 1000) > settings_prov->getThreshold(SettingName::WAIT_TIME)) {
		labelWAITReached->Text = "YES";
	}
	else {
		labelWAITReached->Text = "NO";
	}

	//Sound input
	labelSoundPeak->Text = String::Format("{0:0.00}", system_access->getAudioPeak());

	if (system_access->getAudioPeak() > 0) {
		labelSoundOverLimit->Text = "YES";
	}
	else {
		labelSoundOverLimit->Text = "NO";
	}

	//Log
	if ((textBoxLog->Text != getLogText()) && getLogText() != "") {
		textBoxLog->Text = getLogText();
		textBoxLog->SelectionStart = textBoxLog->TextLength - 1;
		textBoxLog->ScrollToCaret();
	}
}