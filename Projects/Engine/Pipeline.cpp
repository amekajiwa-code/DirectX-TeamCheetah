#include "pch.h"
#include "Pipeline.h"
#include "Texture.h"

Pipeline::Pipeline()
{
	_deviceContext = GRAPHICS()->GetDeviceContext();
}

Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> deviceContext)
{
	_deviceContext = deviceContext;
}

Pipeline::~Pipeline()
{
}

void Pipeline::SetVertexBuffer(shared_ptr<VertexBuffer> buffer)
{
	auto stride = buffer->GetStride();
	auto offset = buffer->GetOffset();

	_deviceContext->IASetVertexBuffers(0, 1, buffer->GetBuffer().GetAddressOf(), &stride, &offset);
}

void Pipeline::SetIndexBuffer(shared_ptr<IndexBuffer> buffer)
{
	_deviceContext->IASetIndexBuffer(buffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
}

void Pipeline::SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture)
{
	if (scope & SS_VertexShader)
		_deviceContext->VSSetShaderResources(slot, 1, texture->GetTexture().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetShaderResources(slot, 1, texture->GetTexture().GetAddressOf());
}
void Pipeline::SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState)
{
	if (scope & SS_VertexShader)
		_deviceContext->VSSetSamplers(slot, 1, samplerState->GetState().GetAddressOf());

	if (scope & SS_PixelShader)
		_deviceContext->PSSetSamplers(slot, 1, samplerState->GetState().GetAddressOf());
}

void Pipeline::Draw(uint32 vertexCount, uint32 startVertexLocation)
{
	_deviceContext->Draw(vertexCount, startVertexLocation);
}

void Pipeline::DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation)
{
	_deviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void Pipeline::UpdatePipeline(Pipelineinfo info)
{
	//IA
	_deviceContext->IASetInputLayout(info.inputLayout->GetLayout().Get());
	_deviceContext->IASetPrimitiveTopology(info.topology);
	//VS
	if (info.vertexShader)
		_deviceContext->VSSetShader(info.vertexShader->GetShader().Get(), nullptr, 0);
	//RS
	if (info.rasterizerState)
		_deviceContext->RSSetState(info.rasterizerState->GetState().Get());
	//PS
	if (info.pixelShader)
		_deviceContext->PSSetShader(info.pixelShader->GetShader().Get(), nullptr, 0);
	//OM
	if (info.blendState)
		_deviceContext->OMSetBlendState(info.blendState->GetState().Get(), info.blendState->GetBlendFactor(), info.blendState->GetSampleMask());
}
