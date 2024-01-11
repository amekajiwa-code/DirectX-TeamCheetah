#pragma once
#include "MetaData.h"

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	ModelRenderer,
	Camera,
	Animator,
	ModelAnimator,
	Script,
	End
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};

class Component
{
	friend class GameObject;
public:
	Component(ComponentType type);
	virtual ~Component();
protected:
	string					_comName;
	ComponentType			_type;
	weak_ptr<GameObject>	_gameObject;
	MetaData				_metaData;
private:
	void SetGameObject(shared_ptr<GameObject> obj) { _gameObject = obj; }
	void SetComponentName(string& name) { _comName = name; }
public:
	string&					GetComponentName() { return _comName; }
	shared_ptr<GameObject>	GetGameObject();
	shared_ptr<Transform>	GetTransform();
	ComponentType			GetType() const { return _type; }
	virtual MetaData&		GetMetaData() { return _metaData; }
public:
	virtual void LoadMetaData(wstring& metaPath){}
	virtual void SaveMetaData(wstring& metaPath){}
public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void FixedUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
};

