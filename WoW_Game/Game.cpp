#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
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
		_vertexBuffer->CreateVertexBuffer(_vertices);
	}
	//index
	{
		_indices = { 0,1,2,2,1,3 };
	}
	//IndexBuffer
	{
		_indexBuffer->CreateIndexBuffer(_indices);
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

	//hr = _graphics->GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	hr = GRAPHICS()->GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());

	CHECK(hr);
}

void Game::CreateInputLayout()
{
	HRESULT hr;

	vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		//{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	_inputLayout->CreateInputLayout(layout, _vsBlob);
}

void Game::CreateVertexShader()
{
	HRESULT hr;

	LoadShaderFromFile(L"Shader/Default.hlsl", "VS", "vs_5_0", _vsBlob);

	//hr = _graphics->GetDevice()->CreateVertexShader(
	//	_vsBlob->GetBufferPointer(),
	//	_vsBlob->GetBufferSize(),
	//	nullptr,
	//	_vertexShader.GetAddressOf()
	//	);

	hr = GRAPHICS()->GetDevice()->CreateVertexShader(
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

	//hr = _graphics->GetDevice()->CreatePixelShader(
	//	_psBlob->GetBufferPointer(),
	//	_psBlob->GetBufferSize(),
	//	nullptr,
	//	_pixelShader.GetAddressOf()
	//);

	hr = GRAPHICS()->GetDevice()->CreatePixelShader(
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

	//hr = _graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	hr = GRAPHICS()->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());

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

	//hr = _graphics->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	hr = GRAPHICS()->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());

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

	//hr = _graphics->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
	hr = GRAPHICS()-> GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());

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
	
	//hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), 
	//	md, _shaderResourceView.GetAddressOf());
	hr = ::CreateShaderResourceView(GRAPHICS()->GetDevice().Get(), img.GetImages(), img.GetImageCount(),
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
	//_graphics = make_shared<Graphics>();
	//GRAPHICS()->SetInstanceAddr(_graphics.get());
	_vertexBuffer = make_shared<VertexBuffer>();
	_indexBuffer = make_shared<IndexBuffer>();
	_inputLayout = make_shared<InputLayout>();

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
	Matrix matScale =  Matrix::CreateScale(_localScale);
	Matrix matRot = Matrix::CreateRotationX(_localRotation.x);
	matRot *= Matrix::CreateRotationY(_localRotation.y);
	matRot *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRot * matTranslation;
	_transformData.matWorld = matWorld;

	D3D11_MAPPED_SUBRESOURCE sub;
	ZeroMemory(&sub, sizeof(sub));

	//_graphics->GetDeviceContext()->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	//::memcpy(sub.pData, &_transformData, sizeof(_transformData));
	GRAPHICS()->GetDeviceContext()->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	::memcpy(sub.pData, &_transformData, sizeof(_transformData));

	//_graphics->GetDeviceContext()->Unmap(_constantBuffer.Get(), 0);
	GRAPHICS()->GetDeviceContext()->Unmap(_constantBuffer.Get(), 0);
}

void Game::Render()
{
	GRAPHICS()->RenderBegin();
	{
		//IA
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		GRAPHICS()->GetDeviceContext()->IASetVertexBuffers(0, 1,
			_vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
		GRAPHICS()->GetDeviceContext()->IASetIndexBuffer(_indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		GRAPHICS()->GetDeviceContext()->IASetInputLayout(_inputLayout->GetLayout().Get());
		GRAPHICS()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//VS
		GRAPHICS()->GetDeviceContext()->VSSetShader(_vertexShader.Get(), nullptr, 0);
		GRAPHICS()->GetDeviceContext()->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
		//RS
		GRAPHICS()->GetDeviceContext()->RSSetState(_rasterizerState.Get());
		//PS
		GRAPHICS()->GetDeviceContext()->PSSetShader(_pixelShader.Get(), nullptr, 0);
		GRAPHICS()->GetDeviceContext()->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		GRAPHICS()->GetDeviceContext()->PSSetSamplers(0, 1, _samplerState.GetAddressOf());
		//OM
		GRAPHICS()->GetDeviceContext()->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);
		//_graphicsContext->Draw(_vertices.size(), 0);
		GRAPHICS()->GetDeviceContext()->DrawIndexed(_indices.size(), 0, 0);
	}
	GRAPHICS()->RenderEnd();
}
