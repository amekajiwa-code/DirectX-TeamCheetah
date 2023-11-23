#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_device = GRAPHICS()->GetDevice();
}

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device)
{
	_device = device;
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::CreateRasterizerState()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;

	hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	//CHECK(hr);
}

void RasterizerState::CreateRasterizerState(const D3D11_RASTERIZER_DESC& desc)
{
	HRESULT hr;

	hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	//CHECK(hr);
}
