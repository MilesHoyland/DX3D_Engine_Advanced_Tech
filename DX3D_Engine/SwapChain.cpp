#include "SwapChain.h"
#include "GraphicsEngine.h"


bool SwapChain::StartUp(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::Get()->m_device;

	//Create swap chain descriptor.
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd)); //..zeros the memory to avoid possible dirty initialisation
	scd.BufferCount = 1;
	scd.BufferDesc.Width = width;												// width of the back buffer
	scd.BufferDesc.Height = height;													// height
	scd.BufferDesc.RefreshRate.Numerator = 60;									// refresh rate: 0 -> do not care
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;								// the color palette to use								
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;		// unspecified scan line ordering
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;						// unspecified scaling
	scd.SampleDesc.Count = 1;													// disable msaa
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;							// use back buffer as render target
	scd.BufferCount = 3;														// the number of buffers in the swap chain (including the front buffer)
	scd.OutputWindow = hwnd;					// set the main window as output target
	scd.Windowed = true;														// windowed, not fullscreen$
	//scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;								// flip mode and discared buffer after presentation
	//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//TODO change to handle with an exeption
	//..create swapchain
	HRESULT hr = GraphicsEngine::Get()->m_dxgi_factory->CreateSwapChain(device,&scd, &m_swap_chain);
	if (FAILED(hr))
	{
		return false;
	}
	
	ID3D11Texture2D* buffer;
	hr = m_swap_chain->GetBuffer(0,__uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, nullptr, &m_render_target_view);
	buffer->Release();
	if (FAILED(hr))
	{
		return false;
	}


	return true;
}

bool SwapChain::ShutDown()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

bool SwapChain::PresentFrame(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	return true;
}
