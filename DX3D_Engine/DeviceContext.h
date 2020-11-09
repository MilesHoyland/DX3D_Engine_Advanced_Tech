#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class GraphicsEngine;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool ShutDown();

	void ClearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertex_buffer);
	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void SetViewPortSize(UINT width, UINT height);

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class GraphicsEngine;
};

