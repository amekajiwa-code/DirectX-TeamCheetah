#include "pch.h"
#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Camera.h"
#include "MeshRenderer.h"

GameObject::GameObject()
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();
}

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
{
	_device = device;
	_deviceContext = deviceContext;
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

	return dynamic_pointer_cast<Camera>(com);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> com = GetFixedComponent(ComponentType::MeshRenderer);

	return dynamic_pointer_cast<MeshRenderer>(com);
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
