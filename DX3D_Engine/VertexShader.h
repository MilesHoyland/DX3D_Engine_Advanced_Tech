#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* render_manager);
	~VertexShader();
private:
	RenderSystem* m_renderer = nullptr;

	ID3D11VertexShader* m_vertex_shader;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

