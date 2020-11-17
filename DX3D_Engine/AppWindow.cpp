#include "AppWindow.h"
#include "VertexBuffer.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};


void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::Get()->StartUp();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->StartUp(this->hwnd, rc.right-rc.left, rc.bottom-rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,	1,0,0}, // POS1
		{-0.5f,0.5f,0.0f,	0,1,0}, // POS2
		{0.5f,-0.5f,0.0f,	0,0,1}, // POS2
		{0.5f,0.5f,0.0f,	1,1,1}, // POS1
	
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	//GraphicsEngine::Get()->CreateShaders();


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	
	//Vertex
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();
	
	//Pixel
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain,
		1, 0.5, 0.5, 1);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

//	GraphicsEngine::Get()->SetShaders();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetSizeVertexList(), 0);
	m_swap_chain->PresentFrame(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vb->Release();
	m_swap_chain->ShutDown();
	m_vs->Release();
	m_ps->Release();
	GraphicsEngine::Get()->ShutDown();
}
