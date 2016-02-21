#pragma once
#include <string>
#include <msclr\marshal_cppstd.h> //Converting System::String to std::string
#include <sstream>

using std::vector;
using std::string;

namespace BasicFunc {
	using namespace System;
	///<summary>Converts a System::String to a std::string</summary>
	string StringToString(System::String^ str);

	///<summary>Splits a string on a defined char and returns vector.</summary>
	std::vector<string> SplitString(const string s, char delim);

	///<summary>Converts a std::string to an int</summary>
	int StringToInt(string str);

	///<summary>Returns an metro font with specified size in points</summary>
	System::Drawing::Font^ getMetroFont(float size);

	///<summary>Returns if an vector of std::string contains a specified std::string</summary>
	bool VectorContains(std::vector<string> list, std::string text);

	///<summary>Returns the log file path and ensures that the file is accessible</summary>
	System::String^ getLogFilePath();

	///<summary>Logs an specified statement or event.</summary>
	void Log(std::string text);

	///<summary>Logs an specified statement or event.</summary>
	void Log(System::String^ text);

	///<summary>Checks if string only contains numerique characters</summary>
	bool isNumerique(std::string text);

	///<summary>Checks if string only contains numerique characters</summary>
	bool isNumerique(System::String^ text);
}
