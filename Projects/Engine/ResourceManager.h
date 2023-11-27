#pragma once
#include "ResourceBase.h"

class Mesh;
class Shader;
class Texture;
class Material;
class Animation;

class ResourceManager
{
	using KeyObjmap = map<wstring, shared_ptr<ResourceBase>>;
private:
	static ResourceManager* _instance;
public:
	static ResourceManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new ResourceManager();

		return _instance;
	}
private:
	ResourceManager();
	~ResourceManager();
private:
	ComPtr<ID3D11Device> _device;
	array<KeyObjmap, RESOURCE_TYPE_COUNT> _resources;
public:
	template<typename T>
	bool AddResource(const wstring& key, shared_ptr<T> obj);
public:
	template<typename T>
	shared_ptr<T> LoadResource(const wstring& key, const wstring& path);
public:
	template<typename T>
	shared_ptr<T> GetResource(const wstring& key);
	template<typename T>
	ResourceType GetResourceType();
private:
	//test
	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();
public:
	void Init();
};

template<typename T>
inline bool ResourceManager::AddResource(const wstring& key, shared_ptr<T> obj)
{
	ResourceType rType = GetResourceType<T>();

	KeyObjmap& kMap = _resources[static_cast<uint8>(rType)];

	auto _find = kMap.find(key);

	if (_find != kMap.end())
		return false;
	else
	{
		kMap[key] = obj;
	}

	return true;
}

template<typename T>
inline shared_ptr<T> ResourceManager::LoadResource(const wstring& key, const wstring& path)
{
	auto objType = GetResourceType<T>();
	KeyObjmap& keyMap = _resources[static_cast<uint8>(objType)];

	auto _find = keyMap.find(key);
	if (_find != keyMap.end())
		return dynamic_pointer_cast<T>(_find->second);

	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyMap[key] = object;

	return object;
}

template<typename T>
inline shared_ptr<T> ResourceManager::GetResource(const wstring& key)
{
	ResourceType rType = GetResourceType<T>();

	KeyObjmap& kMap = _resources[static_cast<uint8>(rType)];

	auto _find = kMap.find(key);

	if (_find != kMap.end())
		return dynamic_pointer_cast<T>(_find->second);
	else
		return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{
	if (std::is_same_v<T, Mesh>)
		return ResourceType::Mesh;

	if (std::is_same_v<T, Shader>)
		return ResourceType::Shader;

	if (std::is_same_v<T, Texture>)
		return ResourceType::Texture;

	if (std::is_same_v<T, Material>)
		return ResourceType::Matertial;

	if (std::is_same_v<T, Animation>)
		return ResourceType::Animation;
		
	assert(false);
	return ResourceType::None;
}
