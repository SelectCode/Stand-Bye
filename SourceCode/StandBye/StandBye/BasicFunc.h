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
#include <string>
#include <msclr\marshal_cppstd.h> //Converting System::String to std::string
#include <sstream>

using std::vector;
using std::string;

ref class BasicFunc {
public:

	///<summary>Converts a System::String to a std::string</summary>
	static string StringToString(System::String^ str);

	///<summary>Splits a string on a defined char and returns vector.</summary>
	static std::vector<string> SplitString(const string s, char delim);

	///<summary>Converts a std::string to an int</summary>
	static int StringToInt(string str);

	///<summary>Returns an metro font with specified size in points</summary>
	static System::Drawing::Font^ getMetroFont(float size);

	///<summary>Returns if an vector of std::string contains a specified std::string</summary>
	static bool VectorContains(std::vector<string> list, std::string text);

	///<summary>Returns the log file path and ensures that the file is accessible</summary>
	static System::String^ getLogFilePath();

	///<summary>Logs an specified statement or event.</summary>
	static void Log(std::string text);

	///<summary>Logs an specified statement or event.</summary>
	static void Log(System::String^ text);

	///<summary>Logs an exception</summary>
	static void Log(System::Exception^ exception);

	///<summary>Opens website in new tab</summary>
	static void openLink(System::String^ url);

	///<summary>Deletes all log files</summary>
	static void cleanLogFiles();
};
