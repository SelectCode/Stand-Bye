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

void BasicFunc::Print(std::string str) {
	//OutputDebugString(_T(str.c_str()));
	//DEBUG(str);
}

System::Drawing::Font^ BasicFunc::getMetroFont(int size) {
	return gcnew System::Drawing::Font(L"Microsoft Sans Serif", size);
}

boolean BasicFunc::VectorContains(std::vector<string> list, std::string text)
{
	boolean result = false;
	for each(std::string s in list) {
		if (s == text) {
			result = true;
		}
	}
	return result;
}