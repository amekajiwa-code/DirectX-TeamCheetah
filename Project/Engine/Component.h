#pragma once

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,

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
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;
private:
	void SetGameObject(shared_ptr<GameObject> obj) { _gameObject = obj; }
public:
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();
	ComponentType GetType() const { return _type; }
public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void FixedUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
};

