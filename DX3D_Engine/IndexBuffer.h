#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list, RenderSystem* render_manager);
	UINT getSizeIndexList();
	~IndexBuffer();

private:
	RenderSystem* m_renderer = nullptr;

	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
private:
	friend class DeviceContext;
};