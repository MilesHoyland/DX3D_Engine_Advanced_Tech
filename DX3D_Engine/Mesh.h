#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	const std::shared_ptr<VertexBuffer>& getVertexBuffer();
	const std::shared_ptr<IndexBuffer>& getIndexBuffer();

private:
	std::shared_ptr<VertexBuffer> m_vertex_buffer;
	std::shared_ptr<IndexBuffer> m_index_buffer;

private:
	friend class DeviceContext;
};

