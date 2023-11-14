#pragma once

class Game
{
private:
	HWND	_hwnd;
	uint32	_width = 0;
	uint32	_height = 0;
private:
	//Device SwapChain
	ComPtr<ID3D11Device>			_device = nullptr;
	ComPtr<ID3D11DeviceContext>		_deviceContext = nullptr;
	ComPtr<IDXGISwapChain>			_swapChain = nullptr;
	//RTV
	ComPtr<ID3D11RenderTargetView>	_renderTargetView;
	//Misc
	D3D11_VIEWPORT					_viewPort = { 0, };
	float _clearColor[4] = { 0.5f,0.5f,0.5f,0.5f };
private:
	std::vector<Vertex>				_vertices;
	ComPtr<ID3D11Buffer>			_vertexBuffer = nullptr;
	ComPtr<ID3D11InputLayout>		_inputLayout = nullptr;
	//vs
	ComPtr<ID3D11VertexShader>		_vertexShader = nullptr;
	ComPtr<ID3DBlob>				_vsBlob = nullptr;
	//ps
	ComPtr<ID3D11PixelShader>		_pixelShader = nullptr;
	ComPtr<ID3DBlob>				_psBlob = nullptr;
public:
	Game();
	~Game();
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewPort();
private:
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVertexShader();
	void CreatePixelShader();
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	void RenderBegin();
	void RenderEnd();
};

