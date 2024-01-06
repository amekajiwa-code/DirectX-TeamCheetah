#pragma once
#include "GUIInterface.h"

class GUIView : public GUIInterface
{
	friend class GUIFile;
	using Super = GUIInterface;
public:
	GUIView();
	virtual ~GUIView();
private:
	bool _showAll = false;

	bool _showAssetSection = false;
	bool _showLoadedAsset = false;
	bool _showScene = false;

	bool _showModelSection = false;
	bool _showBoneHierarchy = false;
	bool _showInspector = false;

	bool _showAnimation = false;
	bool _showGrid = false;
private:
	//Loaded Asset
	ImVec2 _loadedAssetPos;
	ImVec2 _loadedAssetSize;
	//Scene
	ImVec2 _scenePos;
	ImVec2 _sceneSize;
	//BoneHierarchy
	ImVec2 _boneHierarchyPos;
	ImVec2 _boneHierarchySize;
	//Inspector
	ImVec2 _inspectorPos;
	ImVec2 _inspectorSize;
	float _transformPos[3];
	float _transformRot[3];
	float _transformScale [3];
	bool _scaleCheck = false;
	//Animation
	ImVec2 _animationPos;
	ImVec2 _animationSize;

	shared_ptr<Texture> tempTex;

	ComPtr<ID3D11Texture2D> pTex;
	ComPtr<ID3D11ShaderResourceView> pSRV;
private:
	float* ConvertMatrixToFloat(Matrix& mat);
	void HelpMarker(const char* desc);
private:
	//
	void LoadedAsset();
	//
	void Scene();
	void CreateRenderScene();
	//
	void BoneHierarchy();
	//
	void Inspector();
	void Transform();
	void Mesh();
	void Material();
	//
	void Animation();
	//
	void Lighting();
public:
	virtual void Update() override;
	virtual void Render() override;
}; 

