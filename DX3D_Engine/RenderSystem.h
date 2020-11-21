#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

//The DX11 Interface
class RenderSystem
{

public:
	RenderSystem();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~RenderSystem();

	//Wrapper around the device context
private:
	DeviceContext* m_imm_device_context;

//DX11 Member Objects
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

//DX11 Data Member Recources
private:
	//Temporary Data buffers
	//Blobs can be used as data buffers. Can also be used for storing vertex,
	//adjacency, and material information during mesh optimization, and for 
	//loading operations. They iherit the com
	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;

	//ID3D11 - Means, the object inherits from ID3D11DeviceChild.
	//VertexShader and PixelShader objects interface their respective shaders,
	//which are seperate executable programes, and control their stage of the 
	//pipeline.
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

//Friend declarations for access rights
private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
};

