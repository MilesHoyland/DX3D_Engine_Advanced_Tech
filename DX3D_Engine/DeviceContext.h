#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* render_manager);

	void ClearRenderTargetColour(const std::shared_ptr<SwapChain>& swap_chain, float r, float g, float b, float a);
	
	void setIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer);
	void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer);
	
	void setConstantBuffer(const std::shared_ptr<VertexShader>& vertex_shader,const  std::shared_ptr<ConstantBuffer>& buffer);
	void setConstantBuffer(const std::shared_ptr<PixelShader>& pixel_shader, const  std::shared_ptr<ConstantBuffer>& buffer);

	void setTexture(const std::shared_ptr<VertexShader>& vertex_shader, const std::shared_ptr<Texture>& texture);
	void setTexture(const std::shared_ptr<PixelShader>& pixel_shader, const std::shared_ptr<Texture>& texture);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void setViewPortSize(UINT width, UINT height);
	
	void setVertexShader(const std::shared_ptr<VertexShader>& vertex_shader);
	void setPixelShader(const std::shared_ptr<PixelShader>& pixel_shader);

	~DeviceContext();
private:
	RenderSystem* m_renderer;

	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;

};

