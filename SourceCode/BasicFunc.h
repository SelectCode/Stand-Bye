#pragma once
#include <string>
#include <msclr\marshal_cppstd.h> //Converting System::String to std::string
#include <sstream>
using namespace System;

using std::vector;
using std::string;

namespace BasicFunc {
	///<summary>Converts a System::String to a std::string</summary>
	string StringToString(System::String^ str);

	///<summary>Splits a string on a defined char and returns vector.</summary>
	std::vector<string> SplitString(const string s, char delim);

	///<summary>Converts a std::string to an int</summary>
	int StringToInt(string str);

	///<summary>Prints an std::string</summary>
	void Print(string str);

	System::Drawing::Font^ getMetroFont(int size);

	boolean VectorContains(std::vector<string> list, std::string text);
}
