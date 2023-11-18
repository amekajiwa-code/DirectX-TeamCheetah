#pragma once

class RasterizerState
{
private:
	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11RasterizerState>	_rasterizerState;
public:
	RasterizerState();
	RasterizerState(ComPtr<ID3D11Device> device);
	~RasterizerState();
public:
	ComPtr<ID3D11RasterizerState> GetState() { return _rasterizerState; }
public:
	void CreateRasterizerState();
	void CreateRasterizerState(const D3D11_RASTERIZER_DESC& desc);

};

