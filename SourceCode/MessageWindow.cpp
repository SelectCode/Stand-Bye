//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: MessageWindow.cpp
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MessageWindow.h"
using namespace StandBye;

System::Void MessageWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^) {
	this->ControlBox = true;
	this->MaximizeBox = false;
	this->MinimizeBox = false;

	//Gets the Working Space
	Drawing::Rectangle WorkArea = Screen::PrimaryScreen->WorkingArea;
	this->Location = Point((WorkArea.Width - this->Size.Width) / 2, (WorkArea.Height - this->Size.Height) / 2);
	this->Update();
	System::Media::SystemSounds::Asterisk->Play();
}
System::Void MessageWindow::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::OK;
	this->Close();
}
System::Void MessageWindow::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Close();
}