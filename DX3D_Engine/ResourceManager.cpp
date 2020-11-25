#include "ResourceManager.h"

/*Define silence warning for use of std::experimental
* as its now depreciated.
*/
#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

//We need to 
std::shared_ptr<Resource> ResourceManager::createResourceFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::experimental::filesystem::absolute(file_path);

	auto it = m_map_resources.find(full_path);

	if (it != m_map_resources.end())
		return it->second;

	Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str());

	if (raw_res)
	{
		std::shared_ptr<Resource> res(raw_res);
		m_map_resources[full_path] = res;
		return res;
	}
	return nullptr;
}
