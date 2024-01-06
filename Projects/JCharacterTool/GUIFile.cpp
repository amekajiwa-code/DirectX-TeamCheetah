#include "pch.h"
#include "GUIFile.h"
#include "GUIView.h"
#include "engine/Utils.h"
#include "AssetManager.h"
#include "ImGuiManager.h"

GUIFile::GUIFile() : Super(GUIType::File)
{
	_maxDialogSize = ImVec2(g_gameDesc.width, g_gameDesc.height);
	_minDialogSize = _maxDialogSize;
	_minDialogSize.x *= 0.55f;
	_minDialogSize.y *= 0.4f;

	_readsaveDialogPos.x = 0.f;
	_readsaveDialogPos.y = 18.f;

	_type = AssetType::None;
}

GUIFile::~GUIFile()
{
}

MeshPathDesc GUIFile::CreateMeshPathDesc(wstring& fileName, wstring& filePath)
{
	MeshPathDesc desc;
	{
		desc.Name = fileName;
		desc.ReadMeshPath = filePath;
		switch (_type)
		{
		case AssetType::SkeletalMesh:
			desc.SaveMeshPath = RESOURCES_ADDR_MESH_SKELETAL + desc.Name + L"/" + desc.Name + L".mesh";
			desc.SaveMaterialPath = RESOURCES_ADDR_TEXTURE_SKELETAL + desc.Name + L"/" + desc.Name + L".xml";

			break;
		case AssetType::StaticMesh:
			desc.SaveMeshPath = RESOURCES_ADDR_MESH_STATIC + desc.Name + L"/" + desc.Name + L".mesh";
			desc.SaveMaterialPath = RESOURCES_ADDR_TEXTURE_STATIC + desc.Name + L"/" + desc.Name + L".xml";
			break;
		}
	}

	return desc;
}

AnimPathDesc GUIFile::CreateAnimPathDesc(wstring& fileName, wstring& filePath)
{
	return AnimPathDesc();
}

wstring GUIFile::SplitFileName(string name)
{
	string spName = name;
	size_t sp = spName.find_last_of(".");
	wstring rName = Utils::ToWString(spName.substr(0, sp));

	return rName;
}

void GUIFile::MeshReadPoPUp()
{
	if (_isReadMesh)
	{
		ImGui::OpenPopup("Success Mesh Read!");
		if (ImGui::BeginPopupModal("Success Mesh Read!", 0, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::Button("OK", ImVec2(120.f, 20.f)))
			{
				_isReadMesh = false;

				MANAGER_IMGUI()->GetGui<GUIView>()->_showScene = true;
				MANAGER_IMGUI()->GetGui<GUIView>()->_showBoneHierarchy = true;
				MANAGER_IMGUI()->GetGui<GUIView>()->_showInspector = true;
				MANAGER_IMGUI()->GetGui<GUIView>()->_showLoadedAsset = true;


				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}

void GUIFile::MeshSavePoPUp()
{
	if (_isSaveMesh)
	{
		ImGuiWindowFlags saveFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

		ImGui::OpenPopup("Do you want to save the selected Mesh?");
		if (ImGui::BeginPopupModal("Do you want to save the selected Mesh?", 0, saveFlags))
		{
			if (ImGui::Button("Save", ImVec2(150.f, 20.f)))
			{
				string adr;

				if (_type == AssetType::SkeletalMesh)
				{
					adr = Utils::ToString(RESOURCES_ADDR_MESH_SKELETAL);
				}
				else if (_type == AssetType::StaticMesh)
				{
					adr = Utils::ToString(RESOURCES_ADDR_MESH_SKELETAL);
				}

				_dialog.OpenDialog("SaveMesh", "Choose a Directory", ".mesh", adr, 
					"enter a file name");

				_isSaveMesh = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Close", ImVec2(150.f, 20.f)))
			{
				_isSaveMesh = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}

void GUIFile::AnimationReadPoPUp()
{
}

void GUIFile::AnimationSavePoPUp()
{
}

void GUIFile::Update()
{
	//Begin MainMenu
	if (ImGui::BeginMenu("File"))
	{
		//Model Asset
		{
			ImGui::MenuItem("(Mesh)", NULL, false, false);

			//Asset Read
			if (ImGui::BeginMenu("Read Mesh Asset File"))
			{
				if (ImGui::MenuItem("Skeletal"))
				{
					//Dialog Open
					string adr = Utils::ToString(RESOURCES_ADDR_ASSET_SKELETAL);
					_dialog.OpenDialog("ReadModelAssets", "File", ".fbx,.obj",
						adr, 1, nullptr, ImGuiFileDialogFlags_Modal);
					//Asset Type Set
					_type = AssetType::SkeletalMesh;
				}
				if (ImGui::MenuItem("Static"))
				{
					//Dialog Open
					string adr = Utils::ToString(RESOURCES_ADDR_ASSET_STATIC);
					_dialog.OpenDialog("ReadModelAssets", "File", ".fbx,.obj",
						adr, 1, nullptr, ImGuiFileDialogFlags_Modal);
					//Asset Type Set
					_type = AssetType::StaticMesh;
				}
				ImGui::EndMenu();
			}

			//----------------------
			ImGui::Separator();
			//----------------------

			//Save Mesh File
			if (ImGui::MenuItem("Save Mesh Asset File"))
			{
				_isSaveMesh = true;
			}
		}

		//----------------------
		ImGui::Separator();
		//----------------------

		//Animation Asset
		{
			ImGui::MenuItem("(Animation)", NULL, false, false);

			if (ImGui::MenuItem("Read Animation Asset File"))
			{

			}

			//----------------------
			ImGui::Separator();
			//----------------------

			if (ImGui::MenuItem("Save Animation Asset File"))
			{

			}
		}

		//----------------------
		ImGui::Separator();
		//----------------------

		//Effect Asset
		{
			ImGui::MenuItem("(Effect)", NULL, false, false);

			if (ImGui::MenuItem("Read Effect Asset File"))
			{

			}

			if (ImGui::MenuItem("Save Effect Asset File"))
			{

			}
		}

		//End MainMenu
		ImGui::EndMenu();
	}
}

void GUIFile::Render()
{
	//PoPUp
	{
		MeshReadPoPUp();
		MeshSavePoPUp();
	}

	ImGui::SetNextWindowPos(_readsaveDialogPos);

	if (_dialog.Display("ReadModelAssets", ImGuiWindowFlags_NoCollapse, _minDialogSize, _maxDialogSize))
	{
		if (_dialog.IsOk())
		{
			_filePath = Utils::ToWString(_dialog.GetFilePathName());
			_fileName = SplitFileName(_dialog.GetCurrentFileName());

			MeshPathDesc desc = CreateMeshPathDesc(_fileName, _filePath);

			if (MANAGER_ASSET()->ReadMeshAssetFile(desc))
			{
				_isReadMesh = true;
			}
		}
		_dialog.Close();
	}
	if (_dialog.Display("SaveMesh", ImGuiWindowFlags_NoCollapse, _minDialogSize, _maxDialogSize))
	{
		if (_dialog.IsOk())
		{
			_filePath = Utils::ToWString(_dialog.GetCurrentPath());
			_fileName = SplitFileName(_dialog.GetCurrentFileName());
		}
		_dialog.Close();
	}
}

