#include "VertexShader.h"
#include "GraphicsEngine.h"


VertexShader::VertexShader()
{
}

bool VertexShader::Initialise(const void* shader_byte_code, size_t byte_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_device->CreateVertexShader(shader_byte_code, byte_size, nullptr, &m_vertex_shader)))	
		return false;
	
	return true;

}

void VertexShader::Release()
{
	m_vertex_shader->Release();
	delete this;
}

VertexShader::~VertexShader()
{
}
