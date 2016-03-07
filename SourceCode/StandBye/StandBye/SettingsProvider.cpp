//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: SettingsProvider.cpp
 * Author: Florian Baader
 * Contact: contact@stand-bye.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "SettingsProvider.h"
#include "SystemAccess.h" // To avoid cross linking

using namespace System;
using namespace System::IO; //Path.Combine()

SettingsProvider::SettingsProvider() {
	//Load settings
	if (loadSettings()) {
		//Checks if all settings are loaded
		checkSettingsFile();
	}
	else {
		LOG("Settingsfile could not be opend!");
		throw("SettingsFile could not be opend!");
	}
};

SettingsProvider::~SettingsProvider() {
	saveSettingsToFile();
	for each(Setting* s in SettingsList) {
		delete s;
	}
	SettingsList.shrink_to_fit();
}

string SettingsProvider::getRawSetting(SettingName name) {
	try {
		return SettingsProvider::getSettingbyName(name)->GetValue().at(0);
	}
	catch (Exception^ e) {
		LOG("Could not get Raw Setting!");
		LOG(e->Message + "\n" + e->Data + "\n" + e->StackTrace);
		return "";
	}
}

int SettingsProvider::getThreshold(SettingName name) {
	if (static_cast<int>(name) < 5) { //0 to 4 are threshold enumerators
		return BasicFunc::StringToInt(SettingsProvider::getRawSetting(name));
	}
	else {
		LOG("The number of the enumerator should be between 0 and 4");
		throw("No Threshold with this name could be found!");
	}
};

bool SettingsProvider::isActive(SettingName name) {
	if (static_cast<int>(name) > 7) {
		return (SettingsProvider::getRawSetting(name) == "TRUE");
	}
	else {
		LOG("The name should be greater than 6!");
		throw("No valid name entered! Could not convert to boolean!");
	}
}

void SettingsProvider::setActiveState(SettingName name, const bool status) {
	string value = "ERROR";
	if (status == true) {
		value = "TRUE";
	}
	else {
		value = "FALSE";
	}
	getSettingbyName(name)->ChangeValue(value);
}

void SettingsProvider::setSetting(SettingName name, const string value) {
	getSettingbyName(name)->ChangeValue(value);
};

void SettingsProvider::setSetting(SettingName name, const int value) {
	SettingsProvider::setSetting(name, std::to_string(value));
};

vector<string> SettingsProvider::getProcessList() {
	return SettingsProvider::getSettingbyName(SettingName::PROC_EXCP)->GetValue();
};

bool SettingsProvider::addProcessToProcessList(const string process) {
	if (!getSettingbyName(SettingName::PROC_EXCP)->Contains(process)) {
		getSettingbyName(SettingName::PROC_EXCP)->AddValue(process);
		return true;
	}
	else {
		LOG("Process already added");
		return false;
	}
};

void SettingsProvider::removeProcessFromProcessList(const string process) {
	getSettingbyName(SettingName::PROC_EXCP)->RemoveValue(process);
};

bool SettingsProvider::checkSettingsFile() {
	//Resets to DEFAULT values
	bool correction_needed = false;

	using namespace System::Collections;
	vector<Setting*> default_list;
	default_list.push_back(new Setting(SettingName::WAIT_TIME, WAIT_TIME_DEFAULT));
	default_list.push_back(new Setting(SettingName::LANGUAGE, "system"));
	default_list.push_back(new Setting(SettingName::USE_CPU, "TRUE"));
	default_list.push_back(new Setting(SettingName::MAX_CPU, MAX_CPU_DEFAULT));
	default_list.push_back(new Setting(SettingName::USE_RAM, "TRUE"));
	default_list.push_back(new Setting(SettingName::MAX_RAM, MAX_RAM_DEFAULT));
	default_list.push_back(new Setting(SettingName::USE_HDD, "TRUE"));
	default_list.push_back(new Setting(SettingName::MAX_HDD, MAX_HDD_DEFAULT));
	default_list.push_back(new Setting(SettingName::USE_NET, "TRUE"));
	default_list.push_back(new Setting(SettingName::MAX_NET, MAX_NET_DEFAULT));
	default_list.push_back(new Setting(SettingName::CHECK_SOUND, "TRUE"));
	default_list.push_back(new Setting(SettingName::PROC_EXCP, PROC_EXCP_DEFAULT));
	default_list.push_back(new Setting(SettingName::SEARCH_UPDATES, "TRUE"));
	default_list.push_back(new Setting(SettingName::SHOW_MESSAGES, "TRUE"));

	//Ensures that every setting is set
	for each(Setting* default_setting in default_list) {
		bool settting_defined = false;
		for each(Setting* defined_setting in SettingsList) {
			if (defined_setting->GetName() == default_setting->GetName()) {
				settting_defined = true;
			}
		}

		if (!settting_defined) {
			SettingsList.push_back(default_setting);
			LOG("Settings provider added [" + default_setting->GetNameAsString() + "] Setting to file!");
			correction_needed = true;
		}
	}

	if (correction_needed) {
		return writeSettingsFile();
	}
	else {
		return !correction_needed;
	}
};

bool SettingsProvider::saveSettingsToFile()
{
	return writeSettingsFile();
};
vector<Setting*> SettingsProvider::getAllSettings()
{
	return SettingsList;
};

bool SettingsProvider::writeSettingsFile() {
	std::ofstream sFile(getSettingsFilePath());
	if (sFile.is_open()) {
		for each (Setting* set in SettingsList) {
			string all_values = "";

			for each(string val in set->GetValue()) {
				all_values = all_values + "'" + val + +"'" + ",";
			}
			all_values = all_values.substr(0, all_values.length() - 1);
			//If Setting has no value
			if (all_values == "") {
				all_values = "''";
			}
			LOG("Written Setting ['" + set->GetNameAsString() + "'] with value [" + all_values + "]");
			sFile << set->GetNameAsString() << "=" << all_values << std::endl;
		}
		sFile.close();
		return true;
	}
	else {
		//SettingsFile could not be opened!
		LOG("SettingsFile could not be opened to write Settings!");
		throw("SettingsFile could not be opened to write Settings!");
		return false;
	}
};

bool SettingsProvider::loadSettings() {
	string line, name, raw_values;
	std::ifstream sFile(getSettingsFilePath());
	char gsf = "'"[0];
	SettingsList.clear();

	if (sFile.is_open()) {
		while (getline(sFile, line)) {
			//Splits line at '='
			vector<string> splitline = BasicFunc::SplitString(line, '=');
			name = splitline.at(0);

			//Should be 2 --> left & right side of =
			if (splitline.size() > 1) {
				raw_values = splitline.at(1);
			}
			else {
				LOG("Loading settings failed! Resetting file to Factory Settings!");
				return reset();
			}

			//Deletes "'"
			raw_values.erase(std::remove(raw_values.begin(), raw_values.end(), gsf), raw_values.end());

			vector<string> value = BasicFunc::SplitString(raw_values, ',');

			// Creates new Setting
			SettingsList.push_back(new Setting(name, value));
			LOG("Loaded Setting ['" + name + "'] with value ['" + raw_values + "']");
		}
		sFile.close();
		return true;
	}
	else {
		//File could not be opened!
		LOG("SettingsFile could not be opened!");
		checkSettingsFile();
		return false;
	}
}
bool SettingsProvider::reset()
{
	SettingsList.clear();
	SettingsList.push_back(new Setting(SettingName::WAIT_TIME, WAIT_TIME_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_CPU, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_CPU, MAX_CPU_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_RAM, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_RAM, MAX_RAM_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_HDD, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_HDD, MAX_HDD_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_NET, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_NET, MAX_NET_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::CHECK_SOUND, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::PROC_EXCP, PROC_EXCP_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::SEARCH_UPDATES, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::SHOW_MESSAGES, "TRUE"));
	return writeSettingsFile();
}
;

string SettingsProvider::getSettingsFilePath() {
	//Adds the Path to the Settings file
	String^ folder = Path::Combine(SystemAccess::getStandByeFolderPath(), "Settings.ini");
	LOG("Retuned Settings-File-Path: " + folder);
	return BasicFunc::StringToString(folder);
};

Setting* SettingsProvider::getSettingbyName(SettingName name) {
	//Returns setting with equal name

	for each (Setting* set in SettingsList) {
		if (set->GetName() == name) {
			return set;
		}
	}

	LOG("Invalid settingName entered!");
	LOG("Could not get Setting!");
	return nullptr;
};