#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
	_device = GRAPHICS()->GetDevice();
}

Texture::Texture(ComPtr<ID3D11Device> device)
{
	_device = device;
}

Texture::~Texture()
{
}

void Texture::CreateTexture(const wstring& path)
{
	HRESULT hr;
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	//PNG,JPG
	hr = DirectX::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(),
		md, _shaderResourceView.GetAddressOf());
	CHECK(hr);
}
