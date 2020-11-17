#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <d3dcompiler.h>

bool GraphicsEngine::StartUp()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT driver_count = ARRAYSIZE(driver_types);


	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;


	
	for (UINT driver_type_index = 0; driver_type_index < driver_count;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		return false;
	}

	m_device_context = new DeviceContext(m_imm_context);


	//retrieve dxgi - direct x graphics interface
	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	//factory allows us to create swapchain, need pointer

	return true;

}

bool GraphicsEngine::ShutDown()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_factory->Release();
	m_dxgi_adapter->Release();
	m_dxgi_device->Release();

	m_device->Release();
	m_device_context->ShutDown();
	return true;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{

	return new SwapChain;
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_device_context;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer;
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vertex_shader = new VertexShader();
	if (!vertex_shader->Initialise(shader_byte_code, byte_code_size))
	{
		vertex_shader->Release();
		return nullptr;
	}
	return vertex_shader;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* pixel_shader = new PixelShader();
	if (!pixel_shader->Initialise(shader_byte_code, byte_code_size))
	{
		pixel_shader->Release();
		return nullptr;
	}
	return pixel_shader;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}
/*/
bool GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	//D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	//m_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;
}

bool GraphicsEngine::SetShaders()
{
	//m_device_context->m_device_context->VSSetShader(m_vs, nullptr, 0);
	m_device_context->m_device_context->PSSetShader(m_ps, nullptr, 0);
	return true;
}
/*
void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}*/

void GraphicsEngine::ReleaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}
