#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer() : Super(Component(ComponentType::MeshRenderer))
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();

	DefaultInit();
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::DefaultInit()
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	//IA
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_inputLayout = make_shared<InputLayout>(_device);
	//VS
	_vertexShader = make_shared<VertexShader>(_device);
	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	//RS
	_rasterizerState = make_shared<RasterizerState>(_device);
	//PS
	_pixelShader = make_shared<PixelShader>(_device);
	_texture = make_shared<Texture>(_device);
	_samplerState = make_shared<SamplerState>(_device);
	//OM
	_blendState = make_shared<BlendState>(_device);

	_pipeLine = make_shared<Pipeline>();

	wstring texPath = RESOURCES_ADDR_TEXTURE;
	texPath += L"night.png";

	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();
	CreateConstantBuffer();

	CreateRasterizerState();

	CreatePixelShader();
	CreateTexture(texPath);
	CreateSamplerState();

	CreateBlendState();
}

void MeshRenderer::CreateGeometry()
{
	//Vertex data Create
	GeometryHelper::CreateRectangle(_geometry);
	//Vertexbuffer
	_vertexBuffer->CreateVertexBuffer(_geometry->GetVertices());
	//IndexBuffer
	_indexBuffer->CreateIndexBuffer(_geometry->GetIndices());
}

void MeshRenderer::CreateVertexShader()
{
	wstring path = RESOURCES_ADDR_SHADER;
	path += L"Default.hlsl";
	_vertexShader->CreateShader(path, "VS", "vs_5_0");
}

void MeshRenderer::CreateInputLayout()
{
	_inputLayout->CreateInputLayout(VertexTextureData::descs, _vertexShader->GetBlob());
}

void MeshRenderer::CreateConstantBuffer()
{
	_cameraBuffer->CreateConstantBuffer();
	_transformBuffer->CreateConstantBuffer();
}

void MeshRenderer::CreateRasterizerState()
{
	_rasterizerState->CreateRasterizerState();
}

void MeshRenderer::CreatePixelShader()
{
	wstring path = RESOURCES_ADDR_SHADER;
	path += L"Default.hlsl";
	_pixelShader->CreateShader(path, "PS", "ps_5_0");
}

void MeshRenderer::CreateTexture(const wstring& path)
{
	_texture->CreateTexture(path);
}

void MeshRenderer::CreateSamplerState()
{
	_samplerState->CreateSamplerState();
}

void MeshRenderer::CreateBlendState()
{
	_blendState->CreateBlendState();
}

void MeshRenderer::Update()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);

	Render(_pipeLine);
}

void MeshRenderer::Render(shared_ptr<Pipeline> pipeline)
{
	Pipelineinfo info;
	info.vertexShader = _vertexShader;
	info.inputLayout = _inputLayout;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;
	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
