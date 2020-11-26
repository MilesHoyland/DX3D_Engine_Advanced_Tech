#pragma once
#include "Prerequisites.h"
#include <d3d11.h>

//RAII refactor
class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* render_manager);
	bool PresentFrame(bool vsync);

	void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	void resize(unsigned int width, unsigned int height);

	~SwapChain();
private:
	void reloadBuffers(unsigned int width, unsigned int height);
private:
	//render manager
	RenderSystem* m_renderer = nullptr;

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
	ID3D11DepthStencilView* m_depth_stencil_view;
	ID3D11DepthStencilView* m_dsv;
private:
	friend class DeviceContext;
};

