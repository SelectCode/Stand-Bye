#pragma once
#include "stdafx.h"
#include "SettingsProvider.h"

using System::String;

ref class ProcessItem : ListViewItem {
	System::String^ path;
	Bitmap^ icon;
public:
	~ProcessItem();
	ProcessItem(const string settings_value, Windows::Forms::ListView^ list);
	void Write(SettingsProvider* settings_provider);
	String^ GetPath();
	void addIconToLists(Windows::Forms::ListView^ list);
};