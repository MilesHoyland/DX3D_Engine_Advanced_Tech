#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_size, RenderSystem* render_manager);
	~PixelShader();
private:
	RenderSystem* m_renderer = nullptr;

	ID3D11PixelShader* m_pixel_shader;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

