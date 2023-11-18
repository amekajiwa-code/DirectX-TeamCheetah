#pragma once

class Game
{
private:
	HWND	 _hwnd;
private:
	//Geometry
	shared_ptr <Geometry<VertexTextureData>>	_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>					_indexBuffer;
	shared_ptr<InputLayout>					_inputLayout;
	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_constantBuffer;
	//VS
	shared_ptr<VertexShader>		_vertexShader;
	//RS
	ComPtr<ID3D11RasterizerState>	_rasterizerState;
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	//SRV
	shared_ptr<Texture>			_texture;
	//Sampler
	ComPtr<ID3D11SamplerState>		_samplerState;
	//Blend
	ComPtr<ID3D11BlendState>		_blendState;
private:
	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };
public:
	Game();
	~Game();
private:
	void CreateGeometry();
	void CreateConstantBuffer();
	void CreateInputLayout();

	void CreateVertexShader();
	void CreatePixelShader();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateTexture(const wstring& path);
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

