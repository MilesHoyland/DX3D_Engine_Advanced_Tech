#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

//Graphics Engine Singleton
/*
StartUp() - initialise resources
ShutDown() - free recources

*/

class SwapChain;
class DeviceContext;
class VertexBuffer;

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
	VertexBuffer* CreateVertexBuffer();

public:
	bool CreateShaders();
	bool SetShaders();
	void GetShaderBufferAndSize(void** bytecode, UINT* size);

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
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	friend class SwapChain;
	friend class VertexBuffer;

};

