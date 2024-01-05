#pragma once
#include "ModelMesh.h"
#include "ModelAnimation.h"

class Model : public ResourceBase, public enable_shared_from_this<Model>
{
	using Super = ResourceBase;
public:
	Model();
	~Model();
private:
	shared_ptr<ModelBone>			_root;
	vector<shared_ptr<Material>>	_materials;
	vector<shared_ptr<ModelBone>>	_bones;
	vector<shared_ptr<ModelMesh>>	_meshes;
	vector<shared_ptr<ModelAnimation>> _animations;
private:
	ModelType	_modelType = ModelType::None;
	wstring		_modelPath = RESOURCES_ADDR_MESH;
	wstring		_animPath = RESOURCES_ADDR_ANIMATION;
	wstring		_texturePath = RESOURCES_ADDR_TEXTURE;
private:
	void BindCacheInfo();
public:
	uint32 GetMaterialCount() { return static_cast<uint32>(_materials.size()); }
	vector<shared_ptr<Material>>& GetMaterials() { return _materials; }
	shared_ptr<Material> GetMaterialByIndex(uint32 index) { return _materials[index]; }
	shared_ptr<Material> GetMaterialByName(const wstring& name);
public:
	uint32 GetMeshCount() { return static_cast<uint32>(_meshes.size()); }
	vector<shared_ptr<ModelMesh>>& GetMeshes() { return _meshes; }
	shared_ptr<ModelMesh> GetMeshByIndex(uint32 index) { return _meshes[index]; }
	shared_ptr<ModelMesh> GetMeshByName(const wstring& name);
public:
	uint32 GetBoneCount() { return static_cast<uint32>(_bones.size()); }
	vector<shared_ptr<ModelBone>>& GetBones() { return _bones; }
	shared_ptr<ModelBone> GetBoneByIndex(uint32 index) { return (index < 0 || index >= _bones.size() ? nullptr : _bones[index]); }
	shared_ptr<ModelBone> GetBoneByName(const wstring& name);
public:
	uint32 GetAnimationCount() { return _animations.size(); }
	vector<shared_ptr<ModelAnimation>>& GetAnimations() { return _animations; }
	shared_ptr<ModelAnimation> GetAnimationByIndex(UINT index) { return (index < 0 || index >= _animations.size()) ? nullptr : _animations[index]; }
	shared_ptr<ModelAnimation> GetAnimationByName(wstring name);
public:
	ModelType GetModelType() { return _modelType; }
	void	  SetModelType(ModelType type);
public:
	void ReadMaterial(wstring fileName);
	void ReadModel(wstring fileName);
	void ReadAnimation(wstring filename);
public:
	virtual void Save(const wstring& path) override;
};

