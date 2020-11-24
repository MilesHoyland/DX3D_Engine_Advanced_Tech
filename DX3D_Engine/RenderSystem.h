#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

//The DX11 Interface, RenderSystem
class RenderSystem
{
//Public Render System set up functions
public:
	//Initialize the GraphicsEngine and DirectX 11 Device
	RenderSystem();

	//Release all the resources loaded
	~RenderSystem();

//Public Render System Methods
public:
	//Pipeline Creation Methods
	std::shared_ptr<SwapChain> createSwapChain(HWND hwnd, UINT width, UINT height);
	std::shared_ptr<DeviceContext> getImmediateDeviceContext();
	std::shared_ptr<VertexBuffer> createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	std::shared_ptr<IndexBuffer> createIndexBuffer(void* list_indices, UINT size_list);
	std::shared_ptr<ConstantBuffer> createConstantBuffer(void* buffer, UINT size_buffer);
	std::shared_ptr<VertexShader> createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	std::shared_ptr<PixelShader> createPixelShader(const void* shader_byte_code, size_t byte_code_size);

public:
	//Shader Compilation Methods
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

	//Wrapper around the device context
private:
	std::shared_ptr<DeviceContext> m_imm_device_context;

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

