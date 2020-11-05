#include "DeviceContext.h"
#include "SwapChain.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context)
{

}

bool DeviceContext::StartUp()
{
	return true;
}

bool DeviceContext::ShutDown()
{
	m_device_context->Release();
	delete this;
	return true;
}

bool DeviceContext::ClearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float a)
{
	float clear_color[] = { r,g,b,a };
	m_device_context->ClearRenderTargetView(swap_chain->m_render_target_view, clear_color);

	return true;
}

DeviceContext::~DeviceContext()
{
}
