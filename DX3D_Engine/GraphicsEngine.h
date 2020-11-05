#pragma once
#include <d3d11.h>

//Graphics Engine Singleton
/*
StartUp() - initialise resources
ShutDown() - free recources

*/

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine() = default;
	
	static GraphicsEngine* Get()
	{
		static GraphicsEngine sGraphics;
		return &sGraphics;
	}

	bool StartUp();
	bool ShutDown();

public:
	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();

private:
	DeviceContext* m_device_context;

private:
	HWND m_hWnd;

	ID3D11Device* m_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
private:
	friend class SwapChain;
};

