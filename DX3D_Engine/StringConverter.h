#pragma once
#include <string>
#include <locale>
#include <codecvt>

//Singleton for string conversion
class StringConverter
{
public:
	static std::wstring StringToWide(const std::string& str);
	static std::string WideToString(const std::wstring& wstr);
	static std::string WideToString(wchar_t* wstr);
};

