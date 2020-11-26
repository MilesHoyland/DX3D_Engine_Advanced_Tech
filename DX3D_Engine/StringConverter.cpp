#include "StringConverter.h"

std::wstring StringConverter::StringToWide(const std::string& str)
{
	const std::wstring wString(str.begin(), str.end());
	return wString;
}

std::string StringConverter::WideToString(const std::wstring& wstr)
{
	const std::string string(wstr.begin(), wstr.end());
	return string;
}

std::string StringConverter::WideToString(wchar_t* wstr)
{
	std::string string = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);

	return string;
}

