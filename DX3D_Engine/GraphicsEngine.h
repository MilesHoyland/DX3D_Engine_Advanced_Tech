#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include <exception>

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	~GraphicsEngine();
public:
	RenderSystem* getRenderSystem();
public:
	static GraphicsEngine* get();
private:
	RenderSystem* m_render_system = nullptr;

};

