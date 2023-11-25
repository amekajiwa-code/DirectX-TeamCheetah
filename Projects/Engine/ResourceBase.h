#pragma once

enum class ResourceType : uint8
{
	None,
	Mesh,
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

class ResourceBase : public enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();
protected:
	ResourceType _type = ResourceType::None;
	wstring _fileName;
	wstring _filePath;
	uint32	_id = 0;
protected:
	virtual void Load(const wstring& path){}
	virtual void Save(const wstring& path){}
public:
	ResourceType GetType() const { return _type; }
	const wstring& GetName() { return _fileName; }
	uint32 GetID() const { return _id; }
public:
	void SetName(const wstring& name) { _fileName = name; }
	void SetType(const ResourceType& type) { _type = type; }
	void SetPath(const wstring& path) { _filePath = path; }
};

