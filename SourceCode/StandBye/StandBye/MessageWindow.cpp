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
#include "MessageWindow.h"
using namespace StandBye;
using System::Resources::ResourceManager;
using System::Globalization::CultureInfo;
using Windows::Forms::DialogResult;

System::Void MessageWindow::TimeoutWindow_Load(System::Object^, System::EventArgs^) {
	this->ControlBox = true;
	this->MaximizeBox = false;
	this->MinimizeBox = false;

	//Sets Buttons
	ResourceManager^ res_man = gcnew ResourceManager("StandBye.LanguageResources", GetType()->Assembly);
	CultureInfo^ cul = CultureInfo::DefaultThreadCurrentCulture;

	if (buttons == MessageBoxButtons::YesNo) {
		metroButtonOK->Text = res_man->GetString("yes", cul);
		metroButtonCancel->Text = res_man->GetString("no", cul);
	}
	else if (buttons == MessageBoxButtons::OKCancel) {
		metroButtonOK->Text = res_man->GetString("ok", cul);
		metroButtonCancel->Text = res_man->GetString("cancel", cul);
	}
	else if (buttons == MessageBoxButtons::OK) {
		metroButtonOK->Text = res_man->GetString("ok", cul);
		metroButtonCancel->Hide();
	}

	// Sets Back.Image
	ResourceManager^ res_img = gcnew ResourceManager("StandBye.ImageResources.Data", GetType()->Assembly);
	this->BackImage = (System::Drawing::Image^)res_img->GetObject("ICON");

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

void StandBye::MessageWindow::OnClosing(System::Object ^, System::ComponentModel::CancelEventArgs ^)
{
	if (this->DialogResult != Windows::Forms::DialogResult::OK) {
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
	}
}