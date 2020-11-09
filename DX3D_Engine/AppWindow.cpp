#include "AppWindow.h"
#include "VertexBuffer.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 pos;
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
		{-0.5f,-0.5f,0.0f}, // POS1
		{0.0f,0.5f,0.0f}, // POS2
		{ 0.5f,-0.5f,0.0f}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::Get()->CreateShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::Get()->GetShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->Load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);


}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain,
		1, 0, 0, 1);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	GraphicsEngine::Get()->SetShaders();

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleList(m_vb->GetSizeVertexList(), 0);
	m_swap_chain->PresentFrame(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vb->Release();
	m_swap_chain->ShutDown();
	GraphicsEngine::Get()->ShutDown();
}
