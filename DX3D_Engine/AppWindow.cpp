#include "AppWindow.h"

void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::Get()->StartUp();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->StartUp(this->hwnd, rc.right-rc.left, rc.bottom-rc.top);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColour(this->m_swap_chain,
		1,0,0,1);

	m_swap_chain->PresentFrame(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	m_swap_chain->ShutDown();
	GraphicsEngine::Get()->ShutDown();
}
