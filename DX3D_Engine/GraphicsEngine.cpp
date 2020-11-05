#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

bool GraphicsEngine::StartUp()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT driver_count = ARRAYSIZE(driver_types);


	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	ID3D11DeviceContext* m_context;
	for (UINT driver_type_index = 0; driver_type_index < driver_count;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_device, &m_feature_level, &m_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		return false;
	}

	m_device_context = new DeviceContext(m_context);


	//retrieve dxgi - direct x graphics interface
	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	//factory allows us to create swapchain, need pointer

	return true;

}

bool GraphicsEngine::ShutDown()
{
	m_dxgi_factory->Release();
	m_dxgi_adapter->Release();
	m_dxgi_device->Release();

	m_device->Release();
	m_device_context->ShutDown();
	return true;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{

	return new SwapChain;
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_device_context;
}
