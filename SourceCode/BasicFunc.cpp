//////////////////////////////////////////////////////////////////////////
/*!
 * STAND_BYE! SOURCE CODE
 * ----------------------------------------------------------------------
 * for more information see: http://www.stand-bye.de
 * FILE: BasicFunc.cpp
 * Author: Florian Baader
 * Contact: flobaader@web.de
 * Copyright (c) 2016 Florian Baader, Stephan Le, Matthias Weirich
*/
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "BasicFunc.h"

std::string BasicFunc::StringToString(System::String^ str) {
	msclr::interop::marshal_context context;
	std::string fstr = context.marshal_as<std::string>(str);
	return fstr;
};

std::vector<std::string> BasicFunc::SplitString(const std::string s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int BasicFunc::StringToInt(std::string str) {
	std::stringstream stream(str);
	int result;
	stream >> result;
	return result;
}

System::Drawing::Font^ BasicFunc::getMetroFont(float size) {
	return gcnew System::Drawing::Font(L"Microsoft Sans Serif", size);
}

bool BasicFunc::VectorContains(std::vector<string> list, std::string text)
{
	bool result = false;
	for each(std::string s in list) {
		if (s == text) {
			result = true;
		}
	}
	return result;
}

System::String ^ BasicFunc::getLogFilePath()
{
	using namespace System::IO;
	using namespace System::Diagnostics;

	//Startup Time
	DateTime^ starttime = Process::GetCurrentProcess()->StartTime;

	//Path
	//String^ mainFolder = System::IO::Directory::GetCurrentDirectory(); //Programm Directory
	String^ mainFolder = getStandByeAppDataFolderPath();
	String^ log_folder = Path::Combine(mainFolder, "logs");
	String^ current_date_folder = Path::Combine(log_folder, starttime->ToString("yyyy_MM_dd"));
	String^ file_path = Path::Combine(current_date_folder, starttime->ToString("HH_mm") + ".txt");

	//Creates Directory if necessary
	System::IO::Directory::CreateDirectory(current_date_folder);

	return file_path;
}

void BasicFunc::Log(System::String^ text)
{
	//Prints message on Debug-Console
	System::Diagnostics::Debug::WriteLine(text);

	using namespace System::IO;
	using namespace System::Diagnostics;

	//Line
	String^ line = DateTime::Now.ToString("HH:mm:ss:FFF") + "\t" + text;

	//Open Stream
	StreamWriter^ sw;
	try {
		sw = File::AppendText(BasicFunc::getLogFilePath());
	}
	catch (System::Exception^ e) {
		System::Diagnostics::Debug::WriteLine(e->Message);
		System::Diagnostics::Debug::WriteLine(e->StackTrace);
		return;
	}

	//Appends Text
	try {
		sw->WriteLine(line);
	}
	finally
	{
		if (sw)
			delete (IDisposable^)sw;
	}
}

bool BasicFunc::isNumerique(std::string text)
{
	char* p;
	strtol(text.c_str(), &p, 10);
	return *p == 0;
}
bool BasicFunc::isNumerique(System::String ^ text)
{
	return isNumerique(BasicFunc::StringToString(text));
}

System::String ^ BasicFunc::getStandByeAppDataFolderPath()
{
	String^ path = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData);
	path = System::IO::Path::Combine(path, "StandBye");
	return path;
}

void BasicFunc::Log(std::string text)
{
	Log(gcnew String(text.c_str()));
}