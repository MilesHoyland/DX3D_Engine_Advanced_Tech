#include "PixelShader.h"
#include "RenderSystem.h"
#include <exception>


PixelShader::PixelShader(const void* shader_byte_code, size_t byte_size, RenderSystem* render_manager) : m_renderer(render_manager)
{
	if (!SUCCEEDED(m_renderer->m_d3d_device->CreatePixelShader(shader_byte_code, byte_size, nullptr, &m_pixel_shader)))
		throw std::exception("PixelShader not created successfully");

}

PixelShader::~PixelShader()
{
	m_pixel_shader->Release();
}
