#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	bool Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	UINT GetSizeVertexList();
	bool Release();
	~VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
private:
	friend class DeviceContext;
};
