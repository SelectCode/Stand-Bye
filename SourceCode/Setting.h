//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: Setting.h
 * Author: Florian Baader
 * Contact: flobaader@web.de
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
	MAX_CPU, MAX_HDD, MAX_NET, MAX_RAM, WAIT_TIME, PROC_EXCP, NET_ADAPT, USE_CPU, USE_HDD, USE_NET, USE_RAM, CHECK_SOUND, SEARCH_UPDATES, SHOW_MESSAGES
};

class Setting {
private:
	const vector<string> NAME_STRINGS = { "MAX_CPU", "MAX_HDD", "MAX_NET", "MAX_RAM", "WAIT_TIME", "PROC_EXCP", "NET_ADAPT", "USE_CPU", "USE_HDD", "USE_NET", "USE_RAM", "CHECK_SOUND", "SEARCH_UPDATES", "SHOW_MESSAGES" };
	string ConvertSettingNameToString(SettingName n);
	vector<string> value;
	SettingName name;
	SettingName ConvertStringToSettingName(string name);

public:
	Setting(string name, vector<string> values);
	Setting(SettingName name, vector<string> values);
	Setting(SettingName name, string value);
	SettingName GetName();
	vector<string> GetValue();
	void ChangeValue(vector<string> values_changed);
	void ChangeValue(string value_changed);
	void AddValue(string value_new);
	void RemoveValue(string value_remove);
	bool Contains(const string value_find);
	string GetNameAsString();
};
