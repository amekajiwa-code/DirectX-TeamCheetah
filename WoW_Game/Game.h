#pragma once

class Game
{
private:
	HWND					  _hwnd;
	std::shared_ptr<Graphics> _graphics;
private:
	//geometry
	std::vector<Vertex>				_vertices;
	shared_ptr<VertexBuffer>		_vertexBuffer;
	std::vector<uint32>				_indices;
	shared_ptr<IndexBuffer>			_indexBuffer;
	shared_ptr<InputLayout>			_inputLayout;
	//endGeo
	TransformData					_transformData;
	ComPtr<ID3D11Buffer>			_constantBuffer = nullptr;
	//vs
	ComPtr<ID3D11VertexShader>		_vertexShader = nullptr;
	ComPtr<ID3DBlob>				_vsBlob = nullptr;
	//endVs
	//ps
	ComPtr<ID3D11PixelShader>		_pixelShader = nullptr;
	ComPtr<ID3DBlob>				_psBlob = nullptr;
	//rs
	ComPtr<ID3D11RasterizerState>	_rasterizerState = nullptr;

	//srv
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;

	ComPtr<ID3D11SamplerState>		_samplerState = nullptr;
	ComPtr<ID3D11BlendState>		_blendState = nullptr;
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
	void CreateShaderResourceView();
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

