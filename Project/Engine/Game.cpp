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
	wstring path = RESOURCES_ADDR;
	path += L"Shader/Default.hlsl";
	_vertexShader->CreateShader(path, "VS", "vs_5_0");
}

void Game::CreatePixelShader()
{
	wstring path = RESOURCES_ADDR;
	path += L"Shader/Default.hlsl";
	_pixelShader->CreateShader(path, "PS", "ps_5_0");
}

void Game::CreateRasterizerState()
{
	_rasterizerState->CreateRasterizerState();
}

void Game::CreateSamplerState()
{
	_samplerState->CreateSamplerState();
}

void Game::CreateBlendState()
{
	_blendState->CreateBlendState();
}

void Game::CreateTexture(const wstring& path)
{
	_texture->CreateTexture(path);
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	//_graphics = make_shared<Graphics>(_hwnd);
	//IA
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexBuffer = make_shared<VertexBuffer>();
	_indexBuffer = make_shared<IndexBuffer>();
	_inputLayout = make_shared<InputLayout>();
	//VS
	_vertexShader = make_shared<VertexShader>();
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>();
	//RS
	_rasterizerState = make_shared<RasterizerState>();
	//PS
	_pixelShader = make_shared<PixelShader>();
	_texture = make_shared<Texture>();
	_samplerState = make_shared<SamplerState>();
	//OM
	_blendState = make_shared<BlendState>();
	_pipeline = make_shared<Pipeline>();

	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();
	CreateConstantBuffer();

	CreateRasterizerState();

	CreatePixelShader();
	wstring path = RESOURCES_ADDR;
	path += L"Texture/night.png";
	CreateTexture(path);
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
		Pipelineinfo info;
		info.vertexShader = _vertexShader;
		info.inputLayout = _inputLayout;
		info.pixelShader = _pixelShader;
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;

		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(_vertexBuffer);
		_pipeline->SetIndexBuffer(_indexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, _texture);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}
	GRAPHICS()->RenderEnd();
}
