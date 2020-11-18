#include "AppWindow.h"
#include "VertexBuffer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;

	unsigned int m_time;
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
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(0.75f,-0.73f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.5f,0.5f,0.0f),     Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) }
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	constant cc;
	cc.m_time = 0;


	m_cb = GraphicsEngine::Get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));


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

	UpdateQuadPosition();

	GraphicsEngine::Get()->GetImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetSizeVertexList(), 0);
	m_swap_chain->PresentFrame(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
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

void AppWindow::UpdateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 2.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	m_delta_scale += m_delta_time / 2.0f;

//	cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0),Vector3D(2,2,0),m_delta_pos));
	cc.m_world.setScale(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), (sin(m_delta_scale)+1.0f)/2.0f));


	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(this->GetClientWindowRect().right - this->GetClientWindowRect().left) / 400.0f,
		(this->GetClientWindowRect().bottom - this->GetClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);


	m_cb->update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);
}
