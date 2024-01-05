#pragma once
#include "GUIInterface.h"

#pragma region Declaration
struct MeshPathDesc;
struct AnimPathDesc;
#pragma endregion

class GUIFile : public GUIInterface
{
	friend class ImGuiManager;
	using Super = GUIInterface;
public:
	GUIFile();
	virtual ~GUIFile();
private:
	//Cache
	wstring		_filePath;
	wstring		_fileName;
	AssetType	_type;
private:
	//Dialog
	ImVec2 _minDialogSize;
	ImVec2 _maxDialogSize;
	ImVec2 _readsaveDialogPos;
private:
	//UI flag
	//Mesh
	bool _isReadMesh = false;
	bool _isSaveMesh = false;
	//Animation
	bool _isReadAnimation = false;
	bool _isSaveAnimation = false;
	//Effect
	bool _isReadEffect = false;
	bool _isSaveEffect = false;
private:
	//Helper
	MeshPathDesc	CreateMeshPathDesc(wstring& fileName, wstring& filePath);
	AnimPathDesc	CreateAnimPathDesc(wstring& fileName, wstring& filePath);
	wstring			SplitFileName(string name);
private:
	void MeshReadPoPUp();
	void MeshSavePoPUp();
	void AnimationReadPoPUp();
	void AnimationSavePoPUp();
public:
	virtual void Update() override;
	virtual void Render() override;
};

