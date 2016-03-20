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
#pragma once
#include "stdafx.h"
#include "TimeoutWindow.h"
using namespace StandBye;

System::Void TimeoutWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^) {
	LOG("Loading Timeout-Window");
	//Resource Manager
	ResourceManager^ res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
	ResourceManager^ res_icon = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);

	//Language
	CultureInfo^ cul = CultureInfo::DefaultThreadCurrentCulture;

	//Set Form Attributes
	this->BackImage = (System::Drawing::Image^) res_icon->GetObject("ICON");
	metroButtonCancel->Text = res_man->GetString("cancel", cul);
	metroLabelTextTime->Text = res_man->GetString("timeout", cul);

	//Sets other form things;
	this->DoubleBuffered = true;
	this->ControlBox = true;
	this->MaximizeBox = false;
	this->MinimizeBox = false;

	//Loads wait time
	startTimeInTicks = Environment::TickCount;
	lastInputOnStart = (int)SystemAccess::GetLastInputTime();

	//Gets the Working Space
	Drawing::Rectangle WorkArea = Screen::PrimaryScreen->WorkingArea;
	this->Location = Point(WorkArea.Width - this->Size.Width, WorkArea.Height - this->Size.Height);
	this->Update();

	//Starts Time
	timer = gcnew System::Windows::Forms::Timer;
	timer->Interval = 10;
	timer->Tick += gcnew System::EventHandler(this, &TimeoutWindow::RefreshUI);
	timer->Start();

	//Start text
	RefreshUI(nullptr, nullptr);

	//Plays sound
	System::Media::SystemSounds::Asterisk->Play();
	LOG("Timeout-Window loaded");
}

System::Void TimeoutWindow::RefreshUI(System::Object^, System::EventArgs^) {
	int past_millis = Environment::TickCount - startTimeInTicks;

	//If user shows activity the standby can be canceled
	if (SystemAccess::GetLastInputTime() < lastInputOnStart) {
		LOG("The user made an action during displaying");
		metroButtonCancel_Click(nullptr, nullptr);
	}
	else if (past_millis > display_time_in_millis) {
		LOG("The time limit has been reached!");
		metroButtonOK_Click(nullptr, nullptr);
	}
	else {
		//Sets label Text
		metroLabelTime->Text = String::Format("{0:0.00}s", (double)(display_time_in_millis - past_millis) / 1000);

		//Sets Countdown on Button
		metroButtonCancel->Text = "Cancel [" + Math::Truncate((display_time_in_millis - past_millis) / 1000).ToString() + "]";

		//Sets Progress bar
		metroProgressBar1->Value = 100 - (int)Math::Truncate(((double)past_millis / (double)display_time_in_millis) * 100);

		//Ensures that the windows is visible
		this->BringToFront();
		this->Activate();
	}
}
System::Void TimeoutWindow::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::OK;
	LOG("Timeoutwindow returns ok");
	this->Close();
}
System::Void TimeoutWindow::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	LOG("Timeoutwindow returns cancel");
	this->Close();
}