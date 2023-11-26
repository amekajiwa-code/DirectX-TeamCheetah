#include "pch.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Camera.h"

MeshRenderer::MeshRenderer() : Super(Component(ComponentType::MeshRenderer))
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();

	DefaultInit();
}

MeshRenderer::MeshRenderer(shared_ptr<Pipeline> pipe) : Super(Component(ComponentType::MeshRenderer))
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();
	_pipeLine = pipe;
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
	//PS
	_pixelShader = make_shared<PixelShader>(_device);
	_texture = make_shared<Texture>(_device);

	wstring texPath = RESOURCES_ADDR_TEXTURE;
	texPath += L"night.png";

	CreateGeometry();
	CreateVertexShader();
	CreateInputLayout();

	CreatePixelShader();
	CreateTexture(texPath);
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

void MeshRenderer::Update()
{
}

