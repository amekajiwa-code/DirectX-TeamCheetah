#include "pch.h"
#include "Shader.h"

Shader::Shader()
{
	_device = GRAPHICS()->GetDevice();
}

Shader::Shader(ComPtr<ID3D11Device> device)
{
	_device = device;
}

Shader::~Shader()
{
}

void Shader::LoadShaderFromFile(const wstring& path, const string& name, const string& version)
{
	_path = path;
	_name = name;

	HRESULT hr;

#ifdef _DEBUG
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else

#endif // _DEBUG
	hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		_blob.GetAddressOf(),
		nullptr
	);

	CHECK(hr);
}

VertexShader::VertexShader()
{
	_device = GRAPHICS()->GetDevice();
}

VertexShader::VertexShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

VertexShader::~VertexShader()
{
}
void VertexShader::CreateShader(const wstring& path, const string& name, const string& version)
{
	HRESULT hr;
	LoadShaderFromFile(path, name, version);

	hr = _device->CreateVertexShader(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		_vertexShader.GetAddressOf()
	);

	CHECK(hr);
}

PixelShader::PixelShader()
{
	_device = GRAPHICS()->GetDevice();
}

PixelShader::PixelShader(ComPtr<ID3D11Device> device) : Super(device)
{
}

PixelShader::~PixelShader()
{
}
void PixelShader::CreateShader(const wstring& path, const string& name, const string& version)
{
	HRESULT hr;
	LoadShaderFromFile(path, name, version);

	hr = _device->CreatePixelShader(
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		nullptr,
		_pixelShader.GetAddressOf()
	);

	CHECK(hr);
}