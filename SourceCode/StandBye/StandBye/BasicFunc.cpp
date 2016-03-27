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
#include "BasicFunc.h"
#include "SystemAccess.h" //To avoid cross linking

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
	String^ mainFolder = SystemAccess::getStandByeFolderPath();
	String^ log_folder = Path::Combine(mainFolder, "logs");
	String^ current_date_folder = Path::Combine(log_folder, starttime->ToString("yyyy_MM_dd"));
	String^ file_path = Path::Combine(current_date_folder, starttime->ToString("HH_mm") + ".txt");

	//Creates Directory if necessary
	System::IO::Directory::CreateDirectory(current_date_folder);

	return file_path;
}

void BasicFunc::Log(System::String^ text)
{
	using namespace System::IO;
	using namespace System::Diagnostics;

	//Prints message on Debug-Console
	System::Diagnostics::Debug::WriteLine(text);

	//Line
	String^ line = "@" + DateTime::Now.ToString("HH:mm:ss:FFF") + ":" + "\t" + text;

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
	catch (Exception^ e) {
		System::Diagnostics::Debug::WriteLine(e->Message);
		System::Diagnostics::Debug::WriteLine(e->StackTrace);
		return;
	}
	finally
	{
		if (sw)
			delete (IDisposable^)sw;
	}
}
void BasicFunc::Log(System::Exception ^ exception)
{
	Log("Exception occurred!");
	Log("-----------------------");
	Log("\t" + "Message:");
	Log("\t\t" + exception->Message);
	Log("\t" + "Stack:");
	Log("\t\t" + exception->StackTrace);
	Log("-----------------------");
}

void BasicFunc::openLink(System::String^ url)
{
	System::Diagnostics::Process::Start(url);
}

void BasicFunc::cleanLogFiles()
{
	using namespace System::IO;

	String^ mainFolder = SystemAccess::getStandByeFolderPath();
	String^ log_folder = Path::Combine(mainFolder, "logs");
	Directory::Delete(log_folder, true);
}

void BasicFunc::Log(std::string text)
{
	Log(gcnew String(text.c_str()));
}