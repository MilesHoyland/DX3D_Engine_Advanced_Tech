#pragma once
#include <string>

//Singleton for string conversion
class StringConverter
{
public:
	static std::wstring StringToWide(const std::string& str);
	static std::string WideToString(const std::wstring& wstr);
};

