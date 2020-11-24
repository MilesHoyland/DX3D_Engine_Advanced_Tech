#include "LayerStack.h"

LayerStack::LayerStack()
{
	m_layer_inserter = m_layers.begin();
}

LayerStack::~LayerStack()
{
	for (Layer* layer : m_layers)
	{
		delete layer;
	}
}

void LayerStack::pushState(Layer* layer)
{
	m_layer_inserter = m_layers.emplace(m_layer_inserter, layer);
}

void LayerStack::pushOverlay(Layer* overlay)
{
	m_layers.emplace_back(overlay);
}

void LayerStack::popState(Layer* layer)
{
	auto it = std::find(m_layers.begin(), m_layers.end(),layer);
	if (it != m_layers.end())
	{
		m_layers.erase(it);
		m_layer_inserter--;
	}
}

void LayerStack::popOverlay(Layer* layer)
{
	auto it = std::find(m_layers.begin(), m_layers.end(), layer);
	if (it != m_layers.end())
		m_layers.erase(it);
}
