#pragma once
class SamplerState
{
private:
	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11SamplerState>		_samplerState;
public:
	SamplerState();
	SamplerState(ComPtr<ID3D11Device> device);
	~SamplerState();
public:
	ComPtr<ID3D11SamplerState> GetState() { return _samplerState; }
public:
	void CreateSamplerState();
	void CreateSamplerState(const D3D11_SAMPLER_DESC& desc);

};

