#pragma once
#include "Converter.h"

struct AssetData
{
	vector<shared_ptr<asBone>>		bones;
	vector<shared_ptr<asMesh>>		meshes;
	vector<shared_ptr<asMaterial>>	materials;
	shared_ptr<asAnimation>			animation;
};

struct MeshPathDesc
{
	wstring Name;
	wstring ReadMeshPath;
	wstring SaveMeshPath;
	wstring SaveMaterialPath;
	ModelType Type;
};

struct AnimPathDesc
{
	wstring Name;
	wstring ReadAnimPath;
	wstring SaveAnimPath;
};

class AssetManager
{
	using Asset_Dictionary = map<wstring, shared_ptr<GameObject>>;
	using Asset_Data_Dictionary = map<wstring, AssetData>;

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
	Asset_Dictionary				_assets;
	Asset_Data_Dictionary			_assetData;
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
	shared_ptr<GameObject>	GetAssetByName(wstring& name);
	AssetData&				GetAssetDataByName(wstring& name);
public:
	void Init();
	void Update();
	void Clear();
};

#define MANAGER_ASSET() AssetManager::GetInstance()
