#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "ServiceLocator.h"


GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine() 
{
	try {
		m_render_system = new RenderSystem();
	}
	catch (...) { 
		::util::ServiceLocator::getFileLogger()->print<util::SeverityType::error>("RenderSystem failed to initialise.");
		throw std::exception("Render system failed to initialise.");
		return;
	}
	try {
		m_tex_manager = new TextureManager();
	}
	catch (...) {
		::util::ServiceLocator::getFileLogger()->print<util::SeverityType::error>("Texture Manager failed to initialise.");
		throw std::exception("Texture Manager failed to initialise.");
		return;
	}
	::util::ServiceLocator::getFileLogger()->print<util::SeverityType::info>("Graphics engine initialised successfully.");
}


RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

GraphicsEngine::~GraphicsEngine()
{
	
	GraphicsEngine::m_engine = nullptr;
	delete m_tex_manager;
	delete m_render_system;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) throw std::exception("Graphics Engine already created");
	::util::ServiceLocator::getFileLogger()->print<util::SeverityType::info>("Creating graphics engine...");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine) return;
	delete GraphicsEngine::m_engine;
	::util::ServiceLocator::getFileLogger()->print<util::SeverityType::info>("Graphics engine deleted & released.");
}
