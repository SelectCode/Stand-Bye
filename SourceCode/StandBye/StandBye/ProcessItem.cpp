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
#include "ProcessItem.h"
#include "SystemAccess.h"

ProcessItem::ProcessItem(const string settings_value, Windows::Forms::ListView^ list) {
	path = gcnew String(settings_value.c_str());
	icon = SystemAccess::getIconOfProcess(settings_value);
	addIconToLists(list);
	this->Text = IO::Path::GetFileNameWithoutExtension(path);
	this->SubItems->Add(path);
}

void ProcessItem::Write(SettingsProvider* settings_provider) {
	settings_provider->addProcessToProcessList(BasicFunc::StringToString(path));
}

ProcessItem::~ProcessItem() {
	this->ListView->SmallImageList->Images->RemoveAt(this->ListView->Items->IndexOf(this));
	this->ListView->LargeImageList->Images->RemoveAt(this->ListView->Items->IndexOf(this));
	this->Remove();
	delete path;
	delete icon;
}

System::String^ ProcessItem::GetPath() {
	return path;
}

void ProcessItem::addIconToLists(Windows::Forms::ListView^ list)
{
	if (icon) {
		list->SmallImageList->Images->Add(icon);
		list->LargeImageList->Images->Add(icon);
		//The new Item hasn't been added
		this->ImageIndex = list->SmallImageList->Images->Count - 1;
	}
}