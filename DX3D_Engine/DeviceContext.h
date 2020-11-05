#pragma once
#include <d3d11.h>

class SwapChain;


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool StartUp();
	bool ShutDown();

	bool ClearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float a);


	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

};

