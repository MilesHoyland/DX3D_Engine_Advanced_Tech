#pragma once
#include "StringConverter.h"

class Resource
{
public:
	Resource(const wchar_t* full_path);
	virtual ~Resource();

protected:
	std::wstring m_full_path;
};

