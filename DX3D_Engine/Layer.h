#pragma once

#include "SkinnyWindows.h"
#include "StringConverter.h"

class Layer
{
public:
	Layer(const std::string& layerName);
	~Layer();

	virtual void onBindLayer();
	virtual void onUnbindLayer();
	virtual void onUpdate();

	const std::string& GetName() const { return layer_name; }
protected:
	std::string layer_name;
};

