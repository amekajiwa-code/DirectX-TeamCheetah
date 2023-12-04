#pragma once

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~GameObject();
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext>	_deviceContext;
protected:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
public:	
	shared_ptr<Component>		GetFixedComponent(ComponentType type);
public:
	shared_ptr<Transform>		GetTransform();
	shared_ptr<Camera>			GetCamera();
	shared_ptr<MeshRenderer>	GetMeshRenderer();
	//shared_ptr<Animator>		GetAnimator();
public:
	void AddComponent(shared_ptr<Component> component);
public:
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
};
