#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	bool Initialise(const void* shader_byte_code, size_t byte_size);
	void Release();
	~PixelShader();
private:
	ID3D11PixelShader* m_pixel_shader;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

