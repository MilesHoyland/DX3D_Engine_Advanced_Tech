#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, RenderSystem* render_manager);
	UINT GetSizeVertexList();
	~VertexBuffer();
private:
	RenderSystem* m_renderer = nullptr;

	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
private:
	friend class DeviceContext;
};
