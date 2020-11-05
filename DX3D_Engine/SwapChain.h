#pragma once
#include "GraphicsEngine.h"

class DeviceContext;

class SwapChain
{
public:
	SwapChain() = default;

	bool StartUp(HWND hwnd, UINT width, UINT height);
	bool ShutDown();

	bool PresentFrame(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
private:
	friend class DeviceContext;
};

