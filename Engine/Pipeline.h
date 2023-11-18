#pragma once

struct Pipelineinfo
{
	shared_ptr<InputLayout>		inputLayout;
	shared_ptr<VertexShader>		vertexShader;
	shared_ptr<PixelShader>		pixelShader;
	shared_ptr<RasterizerState>	rasterizerState;
	shared_ptr<BlendState>		blendState;
	D3D11_PRIMITIVE_TOPOLOGY		topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{
private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
public:
	Pipeline();
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();
public:
	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);
	template<typename T>
	void SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<T>> buffer)
	{
		if (scope & SS_VertexShader)
			_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetBuffer().GetAddressOf());

		if (scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetBuffer().GetAddressOf());
	}
	void SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);
public:
	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);
public:
	void UpdatePipeline(Pipelineinfo info);
};

