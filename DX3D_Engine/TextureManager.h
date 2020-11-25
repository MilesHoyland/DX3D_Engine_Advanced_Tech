#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	std::shared_ptr<Texture> createTextureFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};

