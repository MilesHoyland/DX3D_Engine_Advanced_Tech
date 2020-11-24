#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* render_manager);

	void ClearRenderTargetColour(std::shared_ptr<SwapChain> swap_chain, float r, float g, float b, float a);
	
	void setIndexBuffer(std::shared_ptr<IndexBuffer> index_buffer);
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> vertex_buffer);
	
	void setConstantBuffer(std::shared_ptr<VertexShader> vertex_shader, std::shared_ptr<ConstantBuffer> buffer);
	void setConstantBuffer(std::shared_ptr<PixelShader> pixel_shader, std::shared_ptr<ConstantBuffer> buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void SetViewPortSize(UINT width, UINT height);
	
	void SetVertexShader(std::shared_ptr<VertexShader> vertex_shader);
	void SetPixelShader(std::shared_ptr<PixelShader> pixel_shader);

	~DeviceContext();
private:
	RenderSystem* m_renderer;

	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;

};

