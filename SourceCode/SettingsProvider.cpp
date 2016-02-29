//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: SettingsProvider.cpp
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "SettingsProvider.h"

using namespace System;
using namespace System::IO; //Path.Combine()

SettingsProvider::SettingsProvider() {
	//Load settings
	if (loadSettings() == false || ((int)SettingsList.size() != SETTINGS_COUNT)) {
		//File does not exists or has not excepted number of settings
		LOG("Settings file could not be loaded or configuration is corrupt!");
		repairFile();
		if (loadSettings() == false) {
			LOG("Settings could not be repaired!");
		}
	};
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
	if (static_cast<int>(name) > 6) {
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

bool SettingsProvider::reset() {
	//Resets to DEFAULT values
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

bool SettingsProvider::saveSettingsToFile()
{
	return writeSettingsFile();
}
vector<Setting*> SettingsProvider::getAllSettings()
{
	return SettingsList;
}
;

bool SettingsProvider::repairFile() {
	std::ifstream sFile(SettingsProvider::getSettingsFilePath());

	if (sFile.is_open()) {
		// File exists but bad configuration --> Reset Configuration
		return SettingsProvider::reset();
	}
	else {
		//Folder does not exist --> Creating Folder
		string StandByeFolderPath = SettingsProvider::getStandByeFolderPath();
		System::IO::Directory::CreateDirectory(gcnew String(StandByeFolderPath.c_str()));
		return SettingsProvider::reset();
	}
	return false;
};

bool SettingsProvider::writeSettingsFile() {
	std::ofstream sFile(SettingsProvider::getSettingsFilePath());
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
	std::ifstream sFile(SettingsProvider::getSettingsFilePath());
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
				repairFile();
				LOG("Loading settings failed! Resetting File to Standard");
				return loadSettings();
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
		return false;
	}
};

string SettingsProvider::getSettingsFilePath() {
	//Gets the AppData Path
	String^ a = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);

	//Adds the Path to the Settings file
	a = Path::Combine(a, "StandBye");
	a = Path::Combine(a, "Settings.ini");

	return BasicFunc::StringToString(a);
};

string SettingsProvider::getStandByeFolderPath() {
	//Gets the AppData Path
	String^ a = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);
	a = Path::Combine(a, "StandBye");
	return BasicFunc::StringToString(a);
};

Setting* SettingsProvider::getSettingbyName(SettingName name) {
	//Returns setting with equal name

	for each (Setting* set in SettingsList) {
		if (set->GetName() == name) {
			return set;
		}
	}
	if (repairFile()) {
		return SettingsProvider::getSettingbyName(name);
	}

	LOG("Invalid settingName entered!");
	LOG("Could not get Setting!");
	return nullptr;
};