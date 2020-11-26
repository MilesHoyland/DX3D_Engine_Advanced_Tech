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
#include "Matrix4x4.h"
#include "LayerStack.h"


class AppWindow : public Window, public InputListener
{
public:

	//App Lifetime Methods
	AppWindow() = default;
	AppWindow(std::string title, std::string windowType)
		: Window(title, windowType)
	{}
	void OnCreate() override;
	void OnDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	
	//App Tick
	void OnUpdate() override;
	

	//Layer Functions
	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	//Input listener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

public:
	//Scene Tick
	void update();
	void updateModel();
	void updateCamera();
	void updateSkyBox();

	//DrawMeshes
	void drawMesh(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<VertexShader>& vs, const std::shared_ptr<PixelShader>& ps, const std::shared_ptr < ConstantBuffer>& cb,
		const std::shared_ptr <Texture>& tex);

	//Render Resources
private:
	std::shared_ptr<SwapChain> m_swap_chain;
	std::shared_ptr<VertexBuffer> m_vb;
	std::shared_ptr<IndexBuffer> m_ib;
	std::shared_ptr<VertexShader> m_vs;

	std::shared_ptr<PixelShader> m_ps;
	std::shared_ptr<PixelShader> m_sky_ps;

	std::shared_ptr<ConstantBuffer> m_cb;
	std::shared_ptr<ConstantBuffer> m_sky_cb;

	std::shared_ptr<Texture> m_wood_tex;
	std::shared_ptr<Texture> m_sky_tex;


	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Mesh> m_sky_mesh;


	//Time Member Data
private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	LayerStack m_layer_stack;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_light_rot_y = 0.0f;


	float m_scale_cube = 1;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	bool cull = true;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;
};

