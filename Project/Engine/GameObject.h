#pragma once
class GameObject
{
public:
	GameObject();
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~GameObject();
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
private:
	//Geometry
	shared_ptr <Geometry<VertexTextureData>>	_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>						_indexBuffer;
	shared_ptr<InputLayout>						_inputLayout;
private:
	//VS
	shared_ptr<VertexShader>					_vertexShader;
	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_constantBuffer;
private:
	//RS
	shared_ptr<RasterizerState>	_rasterizerState;
private:
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	shared_ptr<Texture>			_texture;
	shared_ptr<SamplerState>	_samplerState;
private:
	//OM
	shared_ptr<BlendState>		_blendState;
private:
	//SRT
	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };
	Matrix matScale;
	Matrix matRot;
	Matrix matTranslation;
	Matrix matWorld;
private:
	void DefaultInit();
	void DefaultPipelineSet();
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
private:
	void UpdateMatrix();
public:
	void Update();
	void Render(shared_ptr<Pipeline> pipeline);
};

