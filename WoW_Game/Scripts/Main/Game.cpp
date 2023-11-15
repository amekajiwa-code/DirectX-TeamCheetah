#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::CreateDeviceAndSwapChain()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Game::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr,
		_renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Game::SetViewPort()
{
	_viewPort.TopLeftX = 0.f;
	_viewPort.TopLeftY = 0.f;
	_viewPort.Width = static_cast<float>(_width);
	_viewPort.Height = static_cast<float>(_height);
	_viewPort.MinDepth = 0.f;
	_viewPort.MaxDepth = 1.f;
}

void Game::CreateGeometry()
{
	//vertex data 
	{
		_vertices.resize(4);
		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
		//_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);
		_vertices[0].uv = Vec2(0.f, 1.f);

		_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
		//_vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);
		_vertices[1].uv = Vec2(0.f, 0.f);

		_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
		//_vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);
		_vertices[2].uv = Vec2(1.f, 1.f);

		_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
		//_vertices[3].color = Color(0.f, 0.f, 1.f, 1.f);
		_vertices[3].uv = Vec2(1.f, 0.f);

	}
	//v buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}
	//index
	{
		_indices = { 0,1,2,2,1,3 };
	}
	//IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(uint32) * _indices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _indices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}
}

void Game::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	CHECK(hr);
}

void Game::CreateInputLayout()
{
	HRESULT hr;

	D3D11_INPUT_ELEMENT_DESC mlayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		//{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	const int32 count = sizeof(mlayout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	{
		hr = _device->CreateInputLayout(
			mlayout, 
			count,
			_vsBlob->GetBufferPointer(),
			_vsBlob->GetBufferSize(),
			_inputLayout.GetAddressOf()
		);

		CHECK(hr);
	}
}

void Game::CreateVertexShader()
{
	HRESULT hr;

	LoadShaderFromFile(L"Shader/Default.hlsl", "VS", "vs_5_0", _vsBlob);

	hr = _device->CreateVertexShader(
		_vsBlob->GetBufferPointer(),
		_vsBlob->GetBufferSize(),
		nullptr,
		_vertexShader.GetAddressOf()
		);

	CHECK(hr);
}

void Game::CreatePixelShader()
{
	HRESULT hr;

	LoadShaderFromFile(L"Shader/Default.hlsl", "PS", "ps_5_0", _psBlob);

	hr = _device->CreatePixelShader(
		_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(),
		nullptr,
		_pixelShader.GetAddressOf()
	);

	CHECK(hr);
}

void Game::CreateRasterizerState()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID; 
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;

	hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateSamplerState()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.f;

	hr = _device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateBlendState()
{
	HRESULT hr;
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = _device->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);	
}

void Game::CreateShaderResourceView()
{
	HRESULT hr;
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	//PNG,JPG
	hr = DirectX::LoadFromWICFile(L"../Resources/night.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	
	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), 
		md, _shaderResourceView.GetAddressOf());
	CHECK(hr);

}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
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
		blob.GetAddressOf(),
		nullptr
	);
	CHECK(hr);
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = g_winSizeX;
	_height = g_winSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();

	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();
	CreateRasterizerState();
	CreatePixelShader();

	CreateShaderResourceView();
	CreateSamplerState();
	CreateBlendState();

	CreateConstantBuffer();
}

void Game::Update()
{

	_transformData.offset.x = 0.3f;
	_transformData.offset.y = 0.3f;

	D3D11_MAPPED_SUBRESOURCE sub;
	ZeroMemory(&sub, sizeof(sub));

	_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	::memcpy(sub.pData, &_transformData, sizeof(_transformData));

	_deviceContext->Unmap(_constantBuffer.Get(), 0);
}

void Game::Render()
{
	RenderBegin();

	{
		//IA
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		_deviceContext->IASetVertexBuffers(0, 1, 
			_vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(),DXGI_FORMAT_R32_UINT,0);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());
		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());
		//OM
		_deviceContext->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);
		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_indices.size(), 0, 0);
	}

	RenderEnd();
}

void Game::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewPort);
}

void Game::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}
