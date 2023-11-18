#include "pch.h"
#include "Game.h"

Game::Game()
{
	_hwnd = g_hWnd;
}

Game::~Game()
{
}

void Game::CreateGeometry()
{
	//vertex data 
	GeometryHelper::CreateRectangle(_geometry);
	//vertexbuffer
	_vertexBuffer->CreateVertexBuffer(_geometry->GetVertices());
	//IndexBuffer
	_indexBuffer->CreateIndexBuffer(_geometry->GetIndices());
}

void Game::CreateConstantBuffer()
{
	_constantBuffer->CreateConstantBuffer();
}

void Game::CreateInputLayout()
{
	_inputLayout->CreateInputLayout(VertexTextureData::descs, _vertexShader->GetBlob());
}

void Game::CreateVertexShader()
{
	_vertexShader->CreateShader(L"Shader/Default.hlsl", "VS", "vs_5_0");
}

void Game::CreatePixelShader()
{
	_pixelShader->CreateShader(L"Shader/Default.hlsl", "PS", "ps_5_0");
}

void Game::CreateRasterizerState()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;

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

	hr = GRAPHICS()->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateTexture(const wstring& path)
{
	_texture->CreateTexture(path);
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexBuffer = make_shared<VertexBuffer>();
	_indexBuffer = make_shared<IndexBuffer>();
	_inputLayout = make_shared<InputLayout>();

	_vertexShader = make_shared<VertexShader>();
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>();

	_pixelShader = make_shared<PixelShader>();
	_texture = make_shared<Texture>();

	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();
	CreateConstantBuffer();

	CreateRasterizerState();

	CreatePixelShader();
	CreateTexture(L"../Resources/night.png");
	CreateSamplerState();

	CreateBlendState();
}

void Game::Update()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRot = Matrix::CreateRotationX(_localRotation.x);
	matRot *= Matrix::CreateRotationY(_localRotation.y);
	matRot *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRot * matTranslation;
	_transformData.matWorld = matWorld;

	_constantBuffer->CopyData(_transformData);
}

void Game::Render()
{
	GRAPHICS()->RenderBegin();
	{
		//IA
		uint32 stride = sizeof(VertexTextureData);
		uint32 offset = 0;
		GRAPHICS()->GetDeviceContext()->IASetVertexBuffers(0, 1,
			_vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
		GRAPHICS()->GetDeviceContext()->IASetIndexBuffer(_indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		GRAPHICS()->GetDeviceContext()->IASetInputLayout(_inputLayout->GetLayout().Get());
		GRAPHICS()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//VS
		GRAPHICS()->GetDeviceContext()->VSSetShader(_vertexShader->GetShader().Get(), nullptr, 0);
		GRAPHICS()->GetDeviceContext()->VSSetConstantBuffers(0, 1, _constantBuffer->GetBuffer().GetAddressOf());
		//RS
		GRAPHICS()->GetDeviceContext()->RSSetState(_rasterizerState.Get());
		//PS
		GRAPHICS()->GetDeviceContext()->PSSetShader(_pixelShader->GetShader().Get(), nullptr, 0);
		GRAPHICS()->GetDeviceContext()->PSSetShaderResources(0, 1, _texture->GetTexture().GetAddressOf());
		GRAPHICS()->GetDeviceContext()->PSSetSamplers(0, 1, _samplerState.GetAddressOf());
		//OM
		GRAPHICS()->GetDeviceContext()->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);
		//_graphicsContext->Draw(_vertices.size(), 0);
		GRAPHICS()->GetDeviceContext()->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}
	GRAPHICS()->RenderEnd();
}
