#pragma once

enum class ResourceType : uint8
{
	None,
	Mesh,
	Model,
	Shader,
	Texture,
	Matertial,
	Animation,
	Sound,
	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<uint8>(ResourceType::End) - 1
};

class GameObject;

class ResourceBase : public enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();
protected:
	weak_ptr<GameObject>	_gameObject;
	ResourceType _type = ResourceType::None;
	wstring _name;
	wstring _path;
	uint32	_id = 0;
protected:
	virtual void Load(const wstring& path){}
	virtual void Save(const wstring& path){}
public:
	ResourceType	GetType() const { return _type; }
	const wstring&	GetName() { return _name; }
	const wstring&	GetPath() { return _path; }
	uint32			GetID() const { return _id; }
public:
	void SetGameObject(shared_ptr<GameObject> obj) { _gameObject = obj; }
	void SetName(const wstring& name) { _name = name; }
	void SetType(const ResourceType& type) { _type = type; }
	void SetPath(const wstring& path) { _path = path; }
};

