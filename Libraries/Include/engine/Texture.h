#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
	using Super = ResourceBase;
public:
	Texture();
	Texture(ComPtr<ID3D11Device> device);
	virtual ~Texture();
private:
	ComPtr<ID3D11Device>				_device;
	ComPtr<ID3D11ShaderResourceView>	_shaderResourceView;
	wstring _path;
	Vec2 _size = { 0.f,0.f };
	DirectX::ScratchImage _img = {};
public:
	ComPtr<ID3D11ShaderResourceView> GetTexture() { return _shaderResourceView; }
	Vec2			GetSize() const { return _size; }
	const wstring&	GetPath() { return _path; }
	const DirectX::ScratchImage& GetInfo() { return _img; }
public:
	void CreateTexture(const wstring& path);
public:
	void Load(const wstring& path) override;
};

