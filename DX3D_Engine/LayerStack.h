#pragma once
#include "Layer.h"

#include <vector>

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void pushState(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popState(Layer* layer);
	void popOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_layers.end(); }

private:
	std::vector<Layer*> m_layers;
	std::vector<Layer*>::iterator m_layer_inserter;
};
