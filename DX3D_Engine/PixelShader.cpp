#include "PixelShader.h"
#include "GraphicsEngine.h"


PixelShader::PixelShader()
{
}

bool PixelShader::Initialise(const void* shader_byte_code, size_t byte_size)
{
	if (!SUCCEEDED(GraphicsEngine::Get()->m_device->CreatePixelShader(shader_byte_code, byte_size, nullptr, &m_pixel_shader)))
		return false;

	return true;

}

void PixelShader::Release()
{
	m_pixel_shader->Release();
	delete this;
}

PixelShader::~PixelShader()
{
}
