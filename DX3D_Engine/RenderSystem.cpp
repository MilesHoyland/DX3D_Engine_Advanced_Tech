#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <d3dcompiler.h>
#include <exception>
#include "ServiceLocator.h"

//(1) Initialize the Render Engine and DirectX 11 Device.
RenderSystem::RenderSystem() 
{
	//(1.1) Initi driver type & feature level
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	//(1.1.1) Create the device devices with the provided driver types n feature levels
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		FILE_LOG_ERROR("Render System failed to initialise device.");
		throw(std::exception("Render System failed to initialise driver types for device."));
	}

	m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	initRasterizerState();
}

//Release all the resources loaded
RenderSystem::~RenderSystem()
{
	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_cull_front_state->Release();
	m_cull_back_state->Release();
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_d3d_device->Release();
}



//Swapchain Creation 
std::shared_ptr<SwapChain> RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	std::shared_ptr<SwapChain> sc = nullptr;
	try
	{
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
		FILE_LOG_INFO("SwapChain successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create swapchain"); }
	return sc;
}

//Get Immediate DeviceContext
std::shared_ptr<DeviceContext> RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

std::shared_ptr<VertexBuffer> RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{

	std::shared_ptr<VertexBuffer> vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
		FILE_LOG_INFO("VertexBuffer successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create vertex buffer."); }
	return vb;
}

std::shared_ptr<IndexBuffer> RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	std::shared_ptr<IndexBuffer> ib = nullptr;
	try
	{
		ib = std::make_shared<IndexBuffer>(list_indices, size_list, this);
		FILE_LOG_INFO("IndexBuffer successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create index buffer."); }
	return ib;
}

std::shared_ptr<ConstantBuffer> RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	std::shared_ptr<ConstantBuffer> cb = nullptr;
	try
	{
		cb = std::make_unique<ConstantBuffer>(buffer, size_buffer, this);
		FILE_LOG_INFO("ConstantBuffer successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create constant buffer."); }
	return cb;
}

std::shared_ptr<VertexShader> RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	std::shared_ptr<VertexShader> vs = nullptr;
	try
	{
		vs = std::make_shared<VertexShader>(shader_byte_code, byte_code_size, this);
		FILE_LOG_INFO("VertexShader successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create VertexShader."); }
	return vs;
}

std::shared_ptr<PixelShader> RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	std::shared_ptr<PixelShader> ps = nullptr;
	try
	{
		ps = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
		FILE_LOG_INFO("PixelShader successfully created.");
	}
	catch (...) { FILE_LOG_ERROR("Failed to create PixelShader."); }
	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		FILE_LOG_ERROR("Error in vertex shader compilation.");
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	FILE_LOG_INFO("Vertex Shader successfully compiled.");
	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		FILE_LOG_ERROR("Error in pixel shader compilation.");
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	FILE_LOG_INFO("Pixel Shader successfully compiled.");
	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

void RenderSystem::setRasterizerState(bool cull_front)
{
	if (cull_front)
		m_imm_context->RSSetState(m_cull_front_state);
	else
		m_imm_context->RSSetState(m_cull_back_state);
}

void RenderSystem::initRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;
	m_d3d_device->CreateRasterizerState(&desc, &m_cull_front_state);

	desc.CullMode = D3D11_CULL_BACK;
	m_d3d_device->CreateRasterizerState(&desc, &m_cull_back_state);
}
