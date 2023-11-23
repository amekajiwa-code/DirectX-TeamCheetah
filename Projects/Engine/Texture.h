#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
	using Super = ResourceBase;
private:
	ComPtr<ID3D11Device>				_device;
	ComPtr<ID3D11ShaderResourceView>	_shaderResourceView;
public:
	Texture();
	Texture(ComPtr<ID3D11Device> device);
	~Texture();
public:
	ComPtr<ID3D11ShaderResourceView> GetTexture() { return _shaderResourceView; }
public:
	void CreateTexture(const wstring& path);
};

