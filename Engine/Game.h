#pragma once

class Game
{
private:
	HWND	 _hwnd;
	shared_ptr<Pipeline> _pipeline;
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
	shared_ptr<RasterizerState>	_rasterizerState;
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	//SRV
	shared_ptr<Texture>			_texture;
	//Sampler
	shared_ptr<SamplerState>		_samplerState;
	//Blend
	shared_ptr<BlendState>		_blendState;
private:
	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };
public:
	Game();
	~Game();
private:
	void CreateGeometry();
	void CreateVertexShader();
	void CreateInputLayout();
	void CreateConstantBuffer();

	void CreateRasterizerState();

	void CreatePixelShader();
	void CreateTexture(const wstring& path);
	void CreateSamplerState();

	void CreateBlendState();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

