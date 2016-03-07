//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: TimeoutWindow.cpp
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "TimeoutWindow.h"
using namespace StandBye;

System::Void TimeoutWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^) {
	this->ControlBox = true;
	this->MaximizeBox = false;
	this->MinimizeBox = false;

	//Gets the Working Space
	Drawing::Rectangle WorkArea = Screen::PrimaryScreen->WorkingArea;
	this->Location = Point(WorkArea.Width - this->Size.Width, WorkArea.Height - this->Size.Height);
	this->Update();

	//Starts Time
	timer = gcnew System::Windows::Forms::Timer;
	timer->Interval = 10;
	counter = 0;
	timer->Tick += gcnew System::EventHandler(this, &TimeoutWindow::RefreshUI);
	timer->Start();

	//Plays sound
	System::Media::SystemSounds::Asterisk->Play();
}

System::Void TimeoutWindow::RefreshUI(System::Object^, System::EventArgs^) {
	int past_millis = Environment::TickCount - startTime;

	//If user shows activity the standby can be canceled
	if (SystemAccess::GetLastInputTime() < settings_provider->getThreshold(SettingName::WAIT_TIME)) {
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}

	if (past_millis < delay) {
		metroButtonCancel->Text = "Cancel [" + Math::Truncate((delay - past_millis) / 1000).ToString() + "]";
		this->metroLabelTime->Text = String::Format("{0:0.00}s", (double)(delay - past_millis) / 1000);
		metroProgressBar1->Value = 100 - (int)Math::Truncate(((double)past_millis / (double)delay) * 100);
		counter++;
		this->BringToFront();
		this->Activate();
	}
	else {
		this->DialogResult = Windows::Forms::DialogResult::OK;
		this->Close();
	}
}
System::Void TimeoutWindow::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::OK;
	this->Close();
}
System::Void TimeoutWindow::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Close();
}