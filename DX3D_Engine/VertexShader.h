#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	bool Initialise(const void* shader_byte_code, size_t byte_size);
	void Release();
	~VertexShader();
private:
	ID3D11VertexShader* m_vertex_shader;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

