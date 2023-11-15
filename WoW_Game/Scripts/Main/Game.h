#pragma once

class Game
{
private:
	HWND		_hwnd;
	uint32	_width = 0;
	uint32	_height = 0;
private:
	//Device SwapChain
	ComPtr<ID3D11Device>			_device = nullptr;
	ComPtr<ID3D11DeviceContext>	_deviceContext = nullptr;
	ComPtr<IDXGISwapChain>		_swapChain = nullptr;
	//RTV
	ComPtr<ID3D11RenderTargetView>	_renderTargetView;
	//Misc
	D3D11_VIEWPORT				_viewPort = { 0, };
	float						_clearColor[4] = { 0.f,0.f,0.f,0.f };
private:
	//geometry
	std::vector<Vertex>			_vertices;
	ComPtr<ID3D11Buffer>			_vertexBuffer = nullptr;
	std::vector<uint32>			_indices;
	ComPtr<ID3D11Buffer>			_indexBuffer = nullptr;
	ComPtr<ID3D11InputLayout>		_inputLayout = nullptr;
	TransformData					_transformData;
	ComPtr<ID3D11Buffer>			_constantBuffer = nullptr;
	//vs
	ComPtr<ID3D11VertexShader>		_vertexShader = nullptr;
	ComPtr<ID3DBlob>				_vsBlob = nullptr;
	//ps
	ComPtr<ID3D11PixelShader>		_pixelShader = nullptr;
	ComPtr<ID3DBlob>				_psBlob = nullptr;
	//rs
	ComPtr<ID3D11RasterizerState>	_rasterizerState = nullptr;

	//srv
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;

	ComPtr<ID3D11SamplerState>		_samplerState = nullptr;
	ComPtr<ID3D11BlendState>		_blendState = nullptr;

public:
	Game();
	~Game();
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewPort();
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
private:
	void RenderBegin();
	void RenderEnd();
};

