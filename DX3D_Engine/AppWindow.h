#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow() = default;
	AppWindow(std::string title, std::string windowType)
		: Window(title, windowType)
	{}

	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
};

