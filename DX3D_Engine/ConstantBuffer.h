#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* render_manager);
	void update(DeviceContext* context, void* buffer);
	~ConstantBuffer();
private:
	RenderSystem* m_renderer = nullptr;

	ID3D11Buffer* m_buffer;
private:
	friend class DeviceContext;
};