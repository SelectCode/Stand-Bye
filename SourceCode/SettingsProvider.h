#pragma once
#include "stdafx.h"
#include "Setting.h"
#include "BasicFunc.h"
#include <string>
#include <sstream>
#include <algorithm> //To delete ' in strings
#include <iostream>
#include <fstream>
#include <direct.h> // For creating folders

#define MAX_CPU_DEFAULT "30"                     /*in percent*/
#define MAX_HDD_DEFAULT "2000"                   /*in kBytes/s*/
#define MAX_NET_DEFAULT "1200"                   /*in kBytes/s*/
#define MAX_RAM_DEFAULT "20"                     /*in percent*/
#define WAIT_TIME_DEFAULT "300"                  /*in seconds*/
#define PROC_EXCP_DEFAULT ""                     /*paths to exception processes*/
#define SETTINGS_COUNT 10                        /*to check amount of settings in file*/

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using std::string;
using std::vector;

class SettingsProvider {
	vector<Setting*> SettingsList;

public:
	SettingsProvider();
	~SettingsProvider();

	///<summary>Returns the value of a specified Setting in percent or kbit/s
	///<para>use namespace <code> SettingName:: </code> to get the Names!</para>
	///</summary>
	int getThreshold(SettingName name);

	///<summary>Returns the value of a specified Setting as a std::string
	///<para>use namespace <code> SettingName:: </code> to get the Names!</para>
	///</summary>
	std::string getRawSetting(SettingName name);

	///<summary>Return if selected Metric is active
	///<para>use namespace <code> SettingName:: </code> to get the Names!</para>
	///</summary>
	bool isActive(SettingName name);

	///<summary>Sets if selected Metric should be monitored or not
	///<para>use namespace <code> SettingName:: </code> to get the Names!</para>
	///</summary>
	bool setActiveState(SettingName name, const bool status);

	///<summary>Sets the value for a specified Setting in percent or kbit/s</summary>
	///<param name="limit">The maximum value</param>
	bool setSetting(SettingName name, const int limit);

	///<summary>Sets the value for a specified Setting</summary>
	///<param name="limit">The maximum value</param>
	bool setSetting(SettingName name, const string value);

	///<summary>Returns the set List of blocked Processes</summary>
	vector<string> getProcessList();

	///<summary>Adds one Process to the blocked process list</summary>
	///<param name="process">path of the process</param>
	bool addProcessToProcessList(const string process);

	///<summary>Adds one Process to the blocked process list.</summary>
	///<param name="process">path of the process</param>
	bool removeProcessFromProcessList(const string process);

	///<summary>Resets all settings to factory settings</summary>
	bool reset();

private:

	bool writeSettingsFile();

	bool loadSettings();

	bool repairFile();

	Setting* getSettingbyName(SettingName name);

	string getSettingsFilePath();

	string getAppDataFolderPath();
};
