#pragma once

enum ShaderScope
{
	SS_None = 0,
	SS_VertexShader = (1 << 0),
	SS_PixelShader = (1 << 1),
	SS_Both = SS_VertexShader | SS_PixelShader
};

class ShaderBase
{
protected:
	ComPtr<ID3D11Device>_device;
	ComPtr<ID3DBlob>	_blob;
	wstring				_path;
	string				_name;
public:
	ShaderBase();
	ShaderBase(ComPtr<ID3D11Device> device);
	virtual ~ShaderBase();
public:
	ComPtr<ID3DBlob> GetBlob() const { return _blob; }
public:
	virtual void CreateShader(const wstring& path, const string& name, const string& version) abstract;
protected:
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version);
};

class VertexShader : public ShaderBase
{
	using Super = ShaderBase;
protected:
	ComPtr<ID3D11VertexShader>		_vertexShader;
public:
	VertexShader();
	VertexShader(ComPtr<ID3D11Device> device);
	virtual ~VertexShader();
public:
	ComPtr<ID3D11VertexShader> GetShader() const { return _vertexShader; }
public:
	virtual void CreateShader(const wstring& path, const string& name, const string& version) override;
};

class PixelShader : public ShaderBase
{
	using Super = ShaderBase;
protected:
	ComPtr<ID3D11PixelShader>		_pixelShader;
public:
	PixelShader();
	PixelShader(ComPtr<ID3D11Device> device);
	virtual ~PixelShader();
public:
	ComPtr<ID3D11PixelShader> GetShader() const { return _pixelShader; }
public:
	virtual void CreateShader(const wstring& path, const string& name, const string& version) override;
};