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
#pragma once
#include "stdafx.h"
#include <string>
#include <algorithm>

using std::string;
using std::vector;

enum class SettingName {
	MAX_CPU, MAX_HDD, MAX_NET, MAX_RAM, WAIT_TIME, PROC_EXCP, NET_ADAPT, LANGUAGE, STANDBY_MODE, SLEEPTIME, USE_CPU, USE_HDD, USE_NET, USE_RAM, CHECK_SOUND, SEARCH_UPDATES, SHOW_MESSAGES, LOGGING, USE_SLEEPTIME
};

class Setting {
private:
	vector<string> NAME_STRINGS = { "MAX_CPU", "MAX_HDD", "MAX_NET", "MAX_RAM", "WAIT_TIME", "PROC_EXCP", "NET_ADAPT", "LANGUAGE", "STANDBY_MODE","SLEEPTIME", "USE_CPU", "USE_HDD", "USE_NET", "USE_RAM", "CHECK_SOUND", "SEARCH_UPDATES", "SHOW_MESSAGES", "LOGGING", "USE_SLEEPTIME" };
	vector<string> value;
	SettingName name;

public:
	Setting(string name, vector<string> values);
	Setting(SettingName name, vector<string> values);
	Setting(SettingName name, string value);
	SettingName GetName();
	~Setting()
	{
		NAME_STRINGS.clear();
		NAME_STRINGS.shrink_to_fit();
		value.clear();
		value.shrink_to_fit();
	}
	vector<string> GetValue();
	void ChangeValue(vector<string> values_changed);
	void ChangeValue(string value_changed);
	void AddValue(string value_new);
	void RemoveValue(string value_remove);
	bool Contains(const string value_find);
	string GetNameAsString();

private:
	string ConvertSettingNameToString(SettingName n);
	SettingName ConvertStringToSettingName(string name);
};
