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
#include "Setting.h"

using std::vector;
using std::string;

string Setting::ConvertSettingNameToString(SettingName settingname) {
	return NAME_STRINGS.at(static_cast<int>(settingname));
};

SettingName Setting::ConvertStringToSettingName(string string_name) {
	int counter = 0;
	for each(string s in NAME_STRINGS) {
		if (s == string_name) {
			SettingName n = static_cast<SettingName>(counter);
			return n;
		}
		counter++;
	}
	//The name was not valid
	LOG("No valid name entered!");
	throw("Failed to convert string to SettingName. No valid string entered!");
}

Setting::Setting(string name, vector<string> value) {
	this->name = Setting::ConvertStringToSettingName(name);
	this->value = value;
}

Setting::Setting(SettingName name, vector<string> value) {
	this->name = name;
	this->value = value;
}

Setting::Setting(SettingName name, string value) {
	this->name = name;
	this->value = vector<string>(1, value);
}

SettingName Setting::GetName() {
	return name;
}

vector<string> Setting::GetValue() {
	return value;
}

void Setting::ChangeValue(vector<string> value_changed) {
	value = value_changed;
}

void Setting::ChangeValue(string value_changed) {
	value = vector<string>(1, value_changed);
}

void Setting::AddValue(string value_new) {
	value.push_back(value_new);
}

void Setting::RemoveValue(string value_remove) {
	value.erase(std::remove(value.begin(), value.end(), value_remove), value.end());
}

bool Setting::Contains(const string value_find) {
	return std::find(value.begin(), value.end(), value_find) != value.end();
}

string Setting::GetNameAsString() {
	return Setting::ConvertSettingNameToString(this->name);
}