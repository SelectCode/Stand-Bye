#pragma once
#include "stdafx.h"
#include "SettingsProvider.h"

using namespace System;
using namespace System::IO; //Path.Combine()

SettingsProvider::SettingsProvider() {
	//Load settings
	if (loadSettings() == false || ((int)SettingsList.size() != SETTINGS_COUNT)) {
		//File does not exists or has not excepted number of settings
		DEBUG("Settings file could not be loaded or configuration is corrupt!");
		repairFile();
		if (loadSettings() == false) {
			DEBUG("Settings could not be repaired!");
		}
	};
};

SettingsProvider::~SettingsProvider() {
	for each(Setting* s in SettingsList) {
		delete s;
	}
	SettingsList.shrink_to_fit();
}

string SettingsProvider::getRawSetting(SettingName name) {
	return SettingsProvider::getSettingbyName(name)->GetValue().at(0);
}

int SettingsProvider::getThreshold(SettingName name) {
	if (static_cast<int>(name) < 5) { //0 to 4 are threshold enumerators
		return BasicFunc::StringToInt(SettingsProvider::getRawSetting(name));
	}
	else {
		throw("No Threshold with this name could be found!");
		BasicFunc::Print("The number of the enumerator should be between 0 and 4");
		return 0;
	}
};

bool SettingsProvider::isActive(SettingName name) {
	if (static_cast<int>(name) > 6) {
		return (SettingsProvider::getRawSetting(name) == "TRUE");
	}
	else {
		throw("No valid name entered! Could not convert to boolean!");
		BasicFunc::Print("The name should be greater than 6!");
		return NULL;
	}
}

bool SettingsProvider::setActiveState(SettingName name, bool status) {
	string value = "ERROR";
	if (status == true) {
		value = "TRUE";
	}
	else {
		value = "FALSE";
	}
	getSettingbyName(name)->ChangeValue(value);
	return writeSettingsFile();
}

bool SettingsProvider::setSetting(SettingName name, const string value) {
	getSettingbyName(name)->ChangeValue(value);
	return writeSettingsFile();
};

bool SettingsProvider::setSetting(SettingName name, const int value) {
	return SettingsProvider::setSetting(name, std::to_string(value));
};

vector<string> SettingsProvider::getProcessList() {
	return SettingsProvider::getSettingbyName(SettingName::PROC_EXCP)->GetValue();
};

bool SettingsProvider::addProcessToProcessList(const string process) {
	if (!getSettingbyName(SettingName::PROC_EXCP)->Contains(process)) {
		getSettingbyName(SettingName::PROC_EXCP)->AddValue(process);
		return writeSettingsFile();
	}
	else {
		DEBUG("Process already added");
		return true;
	}
};

bool SettingsProvider::removeProcessFromProcessList(const string process) {
	getSettingbyName(SettingName::PROC_EXCP)->RemoveValue(process);
	return writeSettingsFile();
};

bool SettingsProvider::reset() {
	//Resets to DEFAULT values
	SettingsList.clear();
	SettingsList.push_back(new Setting(SettingName::USE_CPU, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_CPU, MAX_CPU_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_HDD, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_HDD, MAX_HDD_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_NET, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_NET, MAX_NET_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::USE_RAM, "TRUE"));
	SettingsList.push_back(new Setting(SettingName::MAX_RAM, MAX_RAM_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::WAIT_TIME, WAIT_TIME_DEFAULT));
	SettingsList.push_back(new Setting(SettingName::PROC_EXCP, PROC_EXCP_DEFAULT));

	//Returns true if succeeded
	return SettingsProvider::writeSettingsFile();
};

bool SettingsProvider::repairFile() {
	std::ifstream sFile(SettingsProvider::getSettingsFilePath());

	if (sFile.is_open()) {
		// File exists but bad configuration --> Reset Configuration
		return SettingsProvider::reset();
	}
	else {
		//Folder does not exist --> Creating Folder
		string LogoutFolderPath = SettingsProvider::getAppDataFolderPath();
		_mkdir(LogoutFolderPath.c_str());
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
			BasicFunc::Print("Written Setting ['" + set->GetNameAsString() + "'] with value [" + all_values + "]" + "\n");
			sFile << set->GetNameAsString() << "=" << all_values << std::endl;
		}
		sFile.close();
		return true;
	}
	else {
		//SettingsFile could not be opened!
		BasicFunc::Print("SettingsFile could not be opened to write Settings!");
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
				BasicFunc::Print("Loading settings failed! Resetting File to Standard");
				return loadSettings();
			}

			//Deletes "'"
			raw_values.erase(std::remove(raw_values.begin(), raw_values.end(), gsf), raw_values.end());

			vector<string> value = BasicFunc::SplitString(raw_values, ',');

			// Creates new Setting
			SettingsList.push_back(new Setting(name, value));
			BasicFunc::Print("Loaded Setting ['" + name + "'] with value ['" + raw_values + "']\n");
		}
		sFile.close();
		return true;
	}
	else {
		//File could not be opened!
		BasicFunc::Print("SettingsFile could not be opened!");
		return false;
	}
};

string SettingsProvider::getSettingsFilePath() {
	//Gets the AppData Path
	String^ a = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);

	//Adds the Path to the Settings file
	a = Path::Combine(a, "SmartLogout");
	a = Path::Combine(a, "Settings.ini");

	return BasicFunc::StringToString(a);
};

string SettingsProvider::getAppDataFolderPath() {
	//Gets the AppData Path
	String^ a = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);
	a = Path::Combine(a, "SmartLogout");
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
};