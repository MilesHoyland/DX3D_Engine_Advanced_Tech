#pragma once

#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	//Creates a resource from a filepath
	std::shared_ptr<Resource> createResourceFromFile(const wchar_t* file_path);

protected:

	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	//A map to represent the resources through a wstring filepath to a shared resource pointer 
	std::unordered_map<std::wstring, std::shared_ptr<Resource>> m_map_resources;
};
