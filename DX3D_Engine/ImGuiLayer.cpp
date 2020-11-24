#include "ImGuiLayer.h"
#include "imgui.h"
#include "InputSystem.h"

ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiBaseLayer")
{
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui::DestroyContext();
}

//Initialise imgui, set style, create context
void ImGuiLayer::onBindLayer()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	InputSystem::get()->addListener(this);
}

void ImGuiLayer::OnUpdate()
{

}

void ImGuiLayer::onKeyDown(int key)
{
}

void ImGuiLayer::onKeyUp(int key)
{
}

void ImGuiLayer::onMouseMove(const Point& delta_mouse_pos)
{
}

void ImGuiLayer::onLeftMouseDown(const Point& mouse_pos)
{
}

void ImGuiLayer::onLeftMouseUp(const Point& mouse_pos)
{
}

void ImGuiLayer::onRightMouseDown(const Point& mouse_pos)
{
}

void ImGuiLayer::onRightMouseUp(const Point& mouse_pos)
{
}
