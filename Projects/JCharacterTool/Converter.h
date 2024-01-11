#pragma once
#include "AsTypes.h"

class Converter
{
	friend class AssetManager;
public:
	Converter();
	~Converter();
private:
	shared_ptr<Assimp::Importer>	_importer;
	const aiScene*				_scene = nullptr;
	vector<aiNode*>				_nodeList;
	vector<aiNodeAnim*>			_animNodeList;
private:
	vector<shared_ptr<asBone>>		_bones;
	vector<shared_ptr<asMesh>>		_meshes;
	vector<shared_ptr<asMaterial>>	_materials;
	shared_ptr<asAnimation>			_animation;
private:
	wstring _assetPath = RESOURCES_ADDR_ASSET;
	wstring _modelPath = RESOURCES_ADDR_MESH;
	wstring _animPath = RESOURCES_ADDR_ANIMATION;
	wstring _texturePath = RESOURCES_ADDR_TEXTURE;
private:
	//Model
	void ReadModelData(aiNode* node, int32 index, int32 parent);
	void ReadMeshData(aiNode* node, int32 bone);
	void ReadSkinData();
	void WriteModelFile(wstring finalPath);
	void WriteSkinFile(wstring finalPath);
	uint32 GetBoneIndex(const string& name);
private:
	//Material
	bool ReadMaterialData();
	void WriteMaterialData(wstring finalPath);
	string WriteTexture(string saveFolder, string file);
private:
	//Animation
	shared_ptr<asAnimation> ReadAnimationData(aiAnimation* srcAnimation);
	void ReadKeyframeData(shared_ptr<asAnimation> animation, aiNode* node, map<string, shared_ptr<asAnimationNode>>& cache);
	void WriteAnimationData(shared_ptr<asAnimation> animation, wstring finalPath);
	shared_ptr<asAnimationNode> ParseAnimationNode(shared_ptr<asAnimation> animation, aiNodeAnim* srcNode);
public:
	void ExportModelData(wstring savePath);
	void ExportMaterialData(wstring savePath);
	void ExportAnimationData(wstring savePath, uint32 index = 0);
	void ExportAnimationData(wstring& name, wstring& savePath, uint32 index = 0);
public: 
	void Init();
	void ReadAssetFile(ModelType type, wstring fileName);
	bool ReadAssetFile(wstring filePath);

};

