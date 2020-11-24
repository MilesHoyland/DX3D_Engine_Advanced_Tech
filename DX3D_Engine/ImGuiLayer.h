#pragma once

#include "InputListener.h"
#include "Layer.h"

class ImGuiLayer : public Layer, public InputListener
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	virtual void onBindLayer();
	virtual void OnUpdate();

	//Input listener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
private:
	float m_Time = 0.0f;
};

