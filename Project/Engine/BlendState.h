#pragma once
class BlendState
{
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11BlendState>	_blendState;
private:
	float	_blendFactor = 0.f;
	uint32	_sampleMask = 0xFFFFFFFF;
public:
	BlendState();
	BlendState(ComPtr<ID3D11Device> device);
	~BlendState();
public:
	ComPtr<ID3D11BlendState> GetState() const { return _blendState; }
	const float* GetBlendFactor() { return &_blendFactor; }
	uint32 GetSampleMask() const { return _sampleMask; }
public:
	void CreateBlendState(D3D11_RENDER_TARGET_BLEND_DESC blendDesc = {
		true,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_OP_ADD,
		D3D11_COLOR_WRITE_ENABLE_ALL
		}, float factor = 0.f);
	void CreateBlendState(const D3D11_BLEND_DESC& desc, const D3D11_RENDER_TARGET_BLEND_DESC& blendDesc, float factor);
};

