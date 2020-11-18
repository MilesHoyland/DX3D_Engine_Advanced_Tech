#include "AppWindow.h"
#include "VertexBuffer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>
#include "InputSystem.h"

struct vertex
{
	Vector3D position;
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
	GraphicsEngine::get()->StartUp();
	m_swap_chain = GraphicsEngine::get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->StartUp(this->hwnd, rc.right-rc.left, rc.bottom-rc.top);

	InputSystem::get()->addListener(this);


	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	m_vb = GraphicsEngine::get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};


	m_ib = GraphicsEngine::get()->CreateIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);




	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->ReleaseCompiledShader();


	GraphicsEngine::get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->ReleaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::get()->update();
	GraphicsEngine::get()->GetImmediateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain,
		1, 0.5, 0.5, 1);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::get()->GetImmediateDeviceContext()->SetViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	UpdateQuadPosition();

	GraphicsEngine::get()->GetImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->GetImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->GetImmediateDeviceContext()->setIndexBuffer(m_ib);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->GetImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swap_chain->PresentFrame(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}


void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vb->Release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->ShutDown();
	m_vs->Release();
	m_ps->Release();
	GraphicsEngine::get()->ShutDown();
}
void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		m_rot_x += 3.14f * m_delta_time;
	}
	else if (key == 'S')
	{
		m_rot_x -= 3.14f * m_delta_time;
	}
	else if (key == 'A')
	{
		m_rot_y += 3.14f * m_delta_time;
	}
	else if (key == 'D')
	{
		m_rot_y -= 3.14f * m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{

}
void AppWindow::UpdateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 2.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
	
	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 2.0f;

	cc.m_world.setScale(Vector3D(1, 1, 1));

//	cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0),Vector3D(2,2,0),m_delta_pos));
//	cc.m_world.setScale(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), (sin(m_delta_scale)+1.0f)/2.0f));

	temp.setIdentity();
	temp.setRotationZ(0);
	cc.m_world *= temp;
	
	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;



	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(this->GetClientWindowRect().right - this->GetClientWindowRect().left) / 400.0f,
		(this->GetClientWindowRect().bottom - this->GetClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);


	m_cb->update(GraphicsEngine::get()->GetImmediateDeviceContext(), &cc);
}
