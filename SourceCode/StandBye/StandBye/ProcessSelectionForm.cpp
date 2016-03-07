//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: ProcessSelectionForm.cpp
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ProcessSelectionForm.h"
using namespace StandBye;

System::Void ProcessSelectionForm::ProcessSelectionForm_Load(System::Object^, System::EventArgs^) {
	tableLayoutPanel1->Visible = false;

	listViewProc->Font = BasicFunc::getMetroFont(9);
	//Prepare ListView
	ImageList^ imglistSmall = gcnew ImageList, ^imglistLarge = gcnew ImageList;
	imglistSmall->ImageSize = Drawing::Size(24, 24);
	imglistLarge->ImageSize = Drawing::Size(50, 50);
	listViewProc->SmallImageList = imglistSmall;
	listViewProc->LargeImageList = imglistLarge;
}

System::Void ProcessSelectionForm::metroButtonOK_Click(System::Object^, System::EventArgs^) {
	if (listViewProc->SelectedItems->Count > 0) {
		ProcessItem^ p = (ProcessItem^)listViewProc->SelectedItems[0];
		selectedProcessPath = p->GetPath();
		this->DialogResult = Windows::Forms::DialogResult::OK;
	}
	else {
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
	}
	this->Close();
}
System::Void ProcessSelectionForm::metroButtonCancel_Click(System::Object^, System::EventArgs^) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
	this->Close();
}
System::Void ProcessSelectionForm::ProcessSelectioNForm_OnShown(System::Object ^, System::EventArgs ^) {
	for each(std::string path in SystemAccess::GetRunningProccesses()) {
		listViewProc->Items->Add(gcnew ProcessItem(path, listViewProc));
		Application::DoEvents();
	}

	tableLayoutPanel1->Visible = true;
}