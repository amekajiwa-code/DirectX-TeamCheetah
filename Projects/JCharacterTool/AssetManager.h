#pragma once
#include "Converter.h"

struct AssetMeshData
{
	wstring						meshName;
	vector<shared_ptr<asBone>>		bones;
	vector<shared_ptr<asMesh>>		meshes;
	vector<shared_ptr<asMaterial>>	materials;
};

struct AssetAnimData
{
	wstring					animName;
	shared_ptr<asAnimation>	animation;
};

struct MeshPathDesc
{
	wstring Name;
	wstring ReadMeshPath;
	wstring SaveMeshPath;
	wstring SaveMaterialPath;
	ModelType Type = ModelType::None;
};

struct AnimPathDesc
{
	wstring AnimOwnerName;
	wstring AnimName;
	wstring ReadAnimPath;
	wstring SaveAnimPath;
};

class AssetManager
{
	using AssetDictionary = map<wstring, shared_ptr<GameObject>>;
	using MeshDataDictionary = map<wstring, AssetMeshData>;
	using AnimDataDictionary = map<wstring, AssetAnimData>;
private:
	static AssetManager* _instance;
public:
	static AssetManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new AssetManager();

		return _instance;
	}
private:
	AssetManager();
	~AssetManager();
private:
	shared_ptr<Converter>	_converter;
	MeshPathDesc			_meshDesc;
	AnimPathDesc			_animDesc;
private:
	AssetDictionary			_assets;
	MeshDataDictionary		_meshData;
	AnimDataDictionary		_animData;
	vector<shared_ptr<GameObject>>	_currentAssets;
private:
	//Helper Function
public:
	//Read Asset
	bool ReadMeshAssetFile(MeshPathDesc& desc);
	bool ReadAnimAssetFile(AnimPathDesc& desc);
public:
	//Export Asset
	bool ExportMaterialData(wstring& exportPath);
	bool ExportMaterialData(wstring& name, wstring& exportPath);

	bool ExportModelData(wstring& exportPath);
	bool ExportModelData(wstring& name, wstring& exportPath);

	bool ExportAnimationData(wstring& exportPath);
	bool ExportAnimationData(wstring& name, wstring& exportPath);
public:
	bool CreateMeshAsset(MeshPathDesc& desc);
	bool CreateAnimAsset(AnimPathDesc& desc);
public:
	AssetDictionary GetLoadedAssetList() const { return _assets; }
public:
	shared_ptr<GameObject>	GetAssetByName(wstring& name);
	AssetMeshData&			GetMeshDataByName(wstring& name);
	AssetAnimData&			GetAnimDataByName(wstring& name);
public:
	void Init();
	void Update();
	void Clear();
};

#define MANAGER_ASSET() AssetManager::GetInstance()
