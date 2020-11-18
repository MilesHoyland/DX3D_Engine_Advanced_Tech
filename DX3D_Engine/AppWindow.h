#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow() = default;
	AppWindow(std::string title, std::string windowType)
		: Window(title, windowType)
	{}

	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	void UpdateQuadPosition();


private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;

	VertexShader* m_vs;
	PixelShader* m_ps;

	ConstantBuffer* m_cb;

private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
};

