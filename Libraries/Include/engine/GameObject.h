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
	wstring _name;
	bool _isActive = true;
public:	
	void AddComponent(shared_ptr<Component> component);
	template<class T>
	shared_ptr<T>			GetComponent();
	shared_ptr<Component>	GetFixedComponent(ComponentType type);
public:
	shared_ptr<Transform>		GetTransform();
	shared_ptr<Camera>			GetCamera();
	shared_ptr<MeshRenderer>	GetMeshRenderer();
	shared_ptr<ModelRenderer>	GetModelRenderer();
	shared_ptr<ModelAnimator>	GetModelAnimator();
public:
	void SetActive(bool active);
	bool GetActive() { return _isActive; }
	void SetName(wstring& name);
	wstring GetName();
public:
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
};

template<class T>
inline shared_ptr<T> GameObject::GetComponent()
{
	for (const auto& script : _scripts)
	{
		auto castResult = dynamic_pointer_cast<T>(script);

		if (castResult)
			return castResult;
	}

	return nullptr;
}
