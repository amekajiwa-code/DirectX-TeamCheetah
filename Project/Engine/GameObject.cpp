#include "pch.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "Camera.h"

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

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);

	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> com = GetFixedComponent(ComponentType::Transform);

	return dynamic_pointer_cast<Transform>(com);
}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform> trans = make_shared<Transform>();
		AddComponent(trans);
	}

	return GetTransform();
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> com = GetFixedComponent(ComponentType::Camera);

	return static_pointer_cast<Camera>(com);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
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

	DefaultPipelineSet();
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
	_cameraBuffer->CreateConstantBuffer();
	_transformBuffer->CreateConstantBuffer();
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

void GameObject::Awake()
{
	for (shared_ptr<Component>& com : _components)
	{
		if (com)
			com->Awake();
	}

	for (shared_ptr<MonoBehaviour>& com : _scripts)
	{
		com->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& com : _components)
	{
		if (com)
			com->Start();
	}

	for (shared_ptr<MonoBehaviour>& com : _scripts)
	{
		com->Start();
	}
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& com : _components)
	{
		if (com)
			com->FixedUpdate();
	}

	for (shared_ptr<MonoBehaviour>& com : _scripts)
	{
		com->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& com : _components)
	{
		if (com)
			com->Update();
	}

	for (shared_ptr<MonoBehaviour>& com : _scripts)
	{
		com->Update();
	}

	if (GetCamera())
	{
		return;
	}
	//_cameraData.matView = Camera::S_MatView;
	_cameraData.matView = Matrix::Identity;
	//_cameraData.matProjection = Camera::S_MatProjection;
	_cameraData.matProjection = Matrix::Identity;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetOrAddTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& com : _components)
	{
		if (com)
			com->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& com : _scripts)
	{
		com->LateUpdate();
	}
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

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);
	 
	pipeline->SetTexture(0, SS_PixelShader, _texture);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
