#include "stdafx.h"
#include "Setting.h"

using std::vector;
using std::string;

string Setting::ConvertSettingNameToString(SettingName name) {
	return NAME_STRINGS.at(static_cast<int>(name));
};

SettingName Setting::ConvertStringToSettingName(string name) {
	int counter = 0;
	for each(string s in NAME_STRINGS) {
		if (s == name) {
			SettingName n = static_cast<SettingName>(counter);
			return n;
		}
		counter++;
	}
	//The name was not valid
	BasicFunc::Print("No valid name entered!");
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