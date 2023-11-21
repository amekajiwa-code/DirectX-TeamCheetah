#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();

	DefaultInit();
}

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
{
	_device = device;
	_deviceContext = deviceContext;
	DefaultInit();

}

GameObject::~GameObject()
{
}

void GameObject::DefaultInit()
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	//IA
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_inputLayout = make_shared<InputLayout>(_device);
	//VS
	_vertexShader = make_shared<VertexShader>(_device);
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	//RS
	_rasterizerState = make_shared<RasterizerState>(_device);
	//PS
	_pixelShader = make_shared<PixelShader>(_device);
	_texture = make_shared<Texture>(_device);
	_samplerState = make_shared<SamplerState>(_device);
	//OM
	_blendState = make_shared<BlendState>(_device);

	DefaultPipelineSet();

	DefaultComponentSet();
}

void GameObject::DefaultPipelineSet()
{
	wstring texPath = RESOURCES_ADDR;
	texPath += L"Texture/night.png";

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

void GameObject::DefaultComponentSet()
{
	_transform = make_shared<Transform>();
}

void GameObject::CreateGeometry()
{
	//Vertex data Create
	GeometryHelper::CreateRectangle(_geometry);
	//Vertexbuffer
	_vertexBuffer->CreateVertexBuffer(_geometry->GetVertices());
	//IndexBuffer
	_indexBuffer->CreateIndexBuffer(_geometry->GetIndices());
}

void GameObject::CreateVertexShader()
{
	wstring path = RESOURCES_ADDR;
	path += L"Shader/Default.hlsl";
	_vertexShader->CreateShader(path, "VS", "vs_5_0");
}

void GameObject::CreateInputLayout()
{
	_inputLayout->CreateInputLayout(VertexTextureData::descs, _vertexShader->GetBlob());
}

void GameObject::CreateConstantBuffer()
{
	_constantBuffer->CreateConstantBuffer();
}

void GameObject::CreateRasterizerState()
{
	_rasterizerState->CreateRasterizerState();
}

void GameObject::CreatePixelShader()
{
	wstring path = RESOURCES_ADDR;
	path += L"Shader/Default.hlsl";
	_pixelShader->CreateShader(path, "PS", "ps_5_0");
}

void GameObject::CreateTexture(const wstring& path)
{
	_texture->CreateTexture(path);
}

void GameObject::CreateSamplerState()
{
	_samplerState->CreateSamplerState();
}

void GameObject::CreateBlendState()
{
	_blendState->CreateBlendState();
}

void GameObject::Init()
{
}

void GameObject::Update()
{
	Vec3 uPos = _transform->GetPosition();
	uPos.x += 0.001f;
	_transform->SetPosition(uPos);
	_transformData.matWorld = _transform->GetWorldMatrix();

	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
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
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
