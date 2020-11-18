#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class VertexShader;
class ConstantBuffer;
class GraphicsEngine;
class PixelShader;
class IndexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool ShutDown();

	void ClearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float a);
	
	void setIndexBuffer(IndexBuffer* index_buffer);
	void SetVertexBuffer(VertexBuffer* vertex_buffer);
	
	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void SetViewPortSize(UINT width, UINT height);
	
	void SetVertexShader(VertexShader* vertex_shader);
	void SetPixelShader(PixelShader* pixel_shader);

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class GraphicsEngine;
	friend class ConstantBuffer;
};

