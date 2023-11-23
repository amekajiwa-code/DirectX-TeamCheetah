#include "pch.h"
#include "BlendState.h"

BlendState::BlendState()
{
	_device = GRAPHICS()->GetDevice();
}

BlendState::BlendState(ComPtr<ID3D11Device> device)
{
	_device = device;
}

BlendState::~BlendState()
{
}

void BlendState::CreateBlendState(D3D11_RENDER_TARGET_BLEND_DESC blendDesc, float factor)
{
	_blendFactor = factor;

	HRESULT hr;

	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0] = blendDesc;

	hr = _device->CreateBlendState(&desc, _blendState.GetAddressOf());
	//CHECK(hr);
}

void BlendState::CreateBlendState(const D3D11_BLEND_DESC& desc, const D3D11_RENDER_TARGET_BLEND_DESC& blendDesc, float factor)
{
	HRESULT hr;

	D3D11_BLEND_DESC _desc = desc;
	_desc.RenderTarget[0] = blendDesc;

	hr = _device->CreateBlendState(&_desc, _blendState.GetAddressOf());
	//CHECK(hr);
}
