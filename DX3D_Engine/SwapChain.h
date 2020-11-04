#pragma once
#include "GraphicsEngine.h"


class SwapChain
{
public:
	SwapChain() = default;

	bool StartUp(HWND hwnd, UINT width, UINT height);
	bool ShutDown();
private:
	IDXGISwapChain* m_swap_chain;

};

