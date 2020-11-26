#pragma once
#include "ResourceManager.h"


class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	std::shared_ptr<Mesh> createMeshFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};