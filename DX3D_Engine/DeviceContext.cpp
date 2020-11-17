#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context)
{

}



bool DeviceContext::ShutDown()
{
	m_device_context->Release();
	delete this;
	return true;
}

void DeviceContext::ClearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float a)
{
	FLOAT clear_color[] = { r,g,b,a };
	m_device_context->ClearRenderTargetView(swap_chain->m_render_target_view, clear_color);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_render_target_view, NULL);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	//Set the primitive topology to triangle List
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	//Set the primitive topology to triangle strip
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::SetViewPortSize(UINT width, UINT height)
{
	D3D11_VIEWPORT view_port = {};
	view_port.Width = width;
	view_port.Height = height;
	view_port.MinDepth = 0.0f;
	view_port.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &view_port);
}

void DeviceContext::SetVertexShader(VertexShader* vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vertex_shader, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_pixel_shader, nullptr, 0);
}

DeviceContext::~DeviceContext()
{
}
