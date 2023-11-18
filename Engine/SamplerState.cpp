#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{
	_device = GRAPHICS()->GetDevice();
}

SamplerState::SamplerState(ComPtr<ID3D11Device> device)
{
	_device = device;
}

SamplerState::~SamplerState()
{
}

void SamplerState::CreateSamplerState()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.f;

	hr = _device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	CHECK(hr);
}

void SamplerState::CreateSamplerState(const D3D11_SAMPLER_DESC& desc)
{
	HRESULT hr;

	hr = _device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	CHECK(hr);
}
