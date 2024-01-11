#include "pch.h"
#include "GUIView.h"
#include "AssetManager.h"
#include "engine/Utils.h"

static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);

void GUIView::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void GUIView::ButtonManage()
{
	//Exception
	{
		if (!_showLoadedAsset ||
			!_showScene)
		{
			_showAssetSection = false;
		}
		else
		{
			_showAssetSection = true;
		}

		if (!_showInspector ||
			!_showBoneHierarchy)
		{
			_showModelSection = false;
		}
		else
		{
			_showModelSection = true;
		}

		if (!_showAssetSection ||
			!_showLoadedAsset ||
			!_showScene ||
			!_showModelSection ||
			!_showInspector ||
			!_showBoneHierarchy ||
			!_showAnimation)
		{
			_showAll = false;
		}
		else
		{
			_showAll = true;
		}
	}
}

GUIView::GUIView() : Super(GUIType::View)
{
	{
		_loadedAssetPos.x = 0;
		_loadedAssetPos.y = 18.f;
		_loadedAssetSize.x = 350.f;
		_loadedAssetSize.y = 250.f;
	}

	{
		_scenePos.x = 350.f;
		_scenePos.y = 18.f;
		_sceneSize.x = g_gameDesc.width - 700.f;
		_sceneSize.y = 632.f;
	}

	{
		_boneHierarchyPos.x = 0.f;
		_boneHierarchyPos.y = 268.f;
		_boneHierarchySize.x = 350.f;
		_boneHierarchySize.y = 632.f;
	}

	{
		_inspectorPos.x = g_gameDesc.width - 350.f;
		_inspectorPos.y = 268.f;
		_inspectorSize.x = 350.f;
		_inspectorSize.y = 632.f;
	}

	{
		_animationPos.x = 350.f;
		_animationPos.y = 650.f;
		_animationSize.x = 900.f;
		_animationSize.y = 250.f;
	}

	{
		_transformPos[0] = 0.f;
		_transformPos[1] = 0.f;
		_transformPos[2] = 0.f;

		_transformRot[0] = 0.f;
		_transformRot[1] = 0.f;
		_transformRot[2] = 0.f;

		_transformScale[0] = 1.f;
		_transformScale[1] = 1.f;
		_transformScale[2] = 1.f;
	}
}

GUIView::~GUIView()
{
}

void GUIView::LoadedAsset()
{
	if (_showLoadedAsset)
	{
		ImGui::SetNextWindowPos(_loadedAssetPos);
		ImGui::SetNextWindowSize(_loadedAssetSize);
		ImGuiWindowFlags assetFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;

		const map<wstring, shared_ptr<GameObject>>& assetList = MANAGER_ASSET()->GetLoadedAssetList();

		ImGuiTabBarFlags tabBarFlag = ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyResizeDown;

		if (ImGui::Begin("AssetList",&_showLoadedAsset, assetFlags))
		{
			if (ImGui::BeginTabBar("mtbar", tabBarFlag))
			{
				//Skeletal Moddel Tab
				if (ImGui::BeginTabItem("Skeletal"))
				{
					if (ImGui::BeginListBox("##SkeletalTabBox", ImVec2(_loadedAssetSize.x - 15, _loadedAssetSize.y - 58.f)))
					{
						for (auto& asset : assetList)
						{
							ImGui::Selectable(Utils::ToString(asset.second->GetName()).c_str());
						}

						ImGui::EndListBox();
					}

					ImGui::EndTabItem();
				}
				//Static Model Tab
				if (ImGui::BeginTabItem("Static"))
				{
					if (ImGui::BeginListBox("##StaticTabBox", ImVec2(_loadedAssetSize.x - 15, _loadedAssetSize.y - 58.f)))
					{
						for (auto& asset : assetList)
						{
							ImGui::Selectable(Utils::ToString(asset.second->GetName()).c_str());
						}

						ImGui::EndListBox();
					}

					ImGui::EndTabItem();
				}
				//Animation Tab
				if (ImGui::BeginTabItem("Animation"))
				{
					ImGui::EndTabItem();
				}
				//Effect Tab
				if (ImGui::BeginTabItem("Effect"))
				{
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}

void GUIView::Scene()
{
	if (_showScene)
	{
		ImGui::SetNextWindowPos(_scenePos);
		ImGui::SetNextWindowSize(_sceneSize);
		ImGuiWindowFlags scFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;

		MANAGER_ASSET()->Update();

		ImGui::Begin("Scene", &_showScene, scFlags);
		{
			{
				pTex = GRAPHICS()->GetRenderTexture(1).Get();

				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
				srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MostDetailedMip = 0;
				srvDesc.Texture2D.MipLevels = 1;
				DEVICE()->CreateShaderResourceView(pTex.Get(), &srvDesc, pSRV.GetAddressOf());
			}

			ImGui::GetWindowDrawList()->AddImage(
				(void*)pSRV.Get(),
				ImGui::GetCursorScreenPos(),
				ImVec2(ImGui::GetCursorScreenPos().x + _sceneSize.x-15.f, ImGui::GetCursorScreenPos().y + _sceneSize.y-35.f)
			);
		}
		ImGui::End();
	}
}

void GUIView::CreateRenderScene()
{
}

void GUIView::BoneHierarchy()
{
	if (_showBoneHierarchy)
	{
		ImGui::SetNextWindowPos(_boneHierarchyPos);
		ImGui::SetNextWindowSize(_boneHierarchySize);

		ImGuiWindowFlags bhFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;

		if (ImGui::Begin("Bone Hierarchy", &_showBoneHierarchy, bhFlags))
		{
			const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;

			if (ImGui::TreeNodeEx("Bone List", ImGuiTreeNodeFlags_DefaultOpen))
			{
				static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
				static ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAllColumns;
				ImGui::CheckboxFlags("SpanAllColumns", &tree_node_flags, ImGuiTreeNodeFlags_SpanAllColumns);
				ImGui::CheckboxFlags("SpanFullWidth", &tree_node_flags, ImGuiTreeNodeFlags_SpanFullWidth);

				if (ImGui::BeginTable("3ways", 2, flags))
				{
					ImGui::TableSetupColumn("Number", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 5.f);
					ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
					ImGui::TableHeadersRow();

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGuiWindowFlags childFlags = ImGuiWindowFlags_AlwaysHorizontalScrollbar |
						ImGuiWindowFlags_AlwaysVerticalScrollbar;
					if (ImGui::TreeNodeEx("hi", tree_node_flags))
					{
						ImGui::TableNextColumn();
						ImGui::Selectable("sibal");
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						ImGui::Selectable("rgasd");

						ImGui::Selectable("sibsdsal");

						//Ex End
						ImGui::TreePop();

					}
					ImGui::EndTable();
				}
				//Hierarchy End
				ImGui::TreePop();
			}
			if (ImGui::CollapsingHeader("Bone Info", ImGuiTreeNodeFlags_DefaultOpen))
			{

			}

		}
		//Bone Hierarchy End
		ImGui::End();
	}
}

void GUIView::Inspector()
{
	if (_showInspector)
	{
		ImGui::SetNextWindowPos(_inspectorPos);
		ImGui::SetNextWindowSize(_inspectorSize);

		ImGuiWindowFlags insFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;
		//Begin Inspector
		if (ImGui::Begin("Inspector", &_showInspector, insFlags))
		{		
			//Transform
			{
				this->Transform();
			}
			//Mesh
			{
				this->Mesh();
			}
			//Material
			{
				this->Material();
			}
		}
		//End Inspector
		ImGui::End();
	}
}

void GUIView::Transform()
{
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{	
		HelpMarker("If you want, you can adjust Transform by default through mouse drag. Alternatively, you can enter the value directly by double-clicking.");

		//Position
		ImGui::Columns(2);
		ImGui::Separator();
		ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 75.f);
		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::DragFloat3("##Position", _transformPos, 0.01f);
		ImGui::SameLine(0.f, 40.f);
		ImGui::PushID("##PosID");
		if(ImGui::ButtonEx("Reset"))
		{
			_transformPos[0] = 0.f;
			_transformPos[1] = 0.f;
			_transformPos[2] = 0.f;
		}
		ImGui::PopID();
		ImGui::Columns();

		//Rotation
		ImGui::Columns(2);
		ImGui::Separator();
		ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 75.f);
		ImGui::Text("Rotaiotn");
		ImGui::NextColumn();
		ImGui::DragFloat3("##Rotation", _transformRot, 0.01f);
		ImGui::SameLine(0.f, 40.f);
		ImGui::PushID("##RotID");
		if (ImGui::ButtonEx("Reset"))
		{
			_transformRot[0] = 0.f;
			_transformRot[1] = 0.f;
			_transformRot[2] = 0.f;
		}
		ImGui::PopID();
		ImGui::Columns();

		//Scale
		ImGui::Columns(2);
		ImGui::Separator();
		ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 75.f);
		ImGui::Text("Scale");
		ImGui::NextColumn();
		if (ImGui::DragFloat3("##Scale", _transformScale, 0.01f))
		{
			if (_scaleCheck)
			{
				_transformScale[2] = _transformScale[1] = _transformScale[0];
			}
		}
		ImGui::SameLine(0.f, 10.f);
		ImGui::Checkbox("##scaleCheck", &_scaleCheck);
		ImGui::SetItemTooltip("If this CheckBox is checked, All elements of the Scale\nincrease and decrease equally depending on the value of X.");
		ImGui::SameLine(0.f, 11.f);
		ImGui::PushID("##ScaleID");
		if (ImGui::ButtonEx("Reset"))
		{
			_transformScale[0] = 1.f;
			_transformScale[1] = 1.f;
			_transformScale[2] = 1.f;
		}
		ImGui::PopID();
		ImGui::Columns();
	}
}

void GUIView::Mesh()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}

void GUIView::Material()
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}

void GUIView::Animation()
{
	if (_showAnimation)
	{
		ImGui::SetNextWindowPos(_animationPos);
		ImGui::SetNextWindowSize(_animationSize);

		ImGuiWindowFlags aniFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;
		//Begin Inspector
		if (ImGui::Begin("Animation", &_showAnimation, aniFlags))
		{
		}
		//End Inspector
		ImGui::End();
	}
}

void GUIView::Lighting()
{
}

float* GUIView::ConvertMatrixToFloat(Matrix& mat)
{
	float ReturnFloat[16] = { 0, };

	ReturnFloat[0] = mat._11; ReturnFloat[1] = mat._12; ReturnFloat[2] = mat._13; ReturnFloat[3] = mat._14;
	ReturnFloat[4] = mat._21; ReturnFloat[5] = mat._22; ReturnFloat[6] = mat._23; ReturnFloat[7] = mat._24;
	ReturnFloat[8] = mat._31; ReturnFloat[9] = mat._32; ReturnFloat[10] = mat._33; ReturnFloat[11] = mat._34;
	ReturnFloat[12] = mat._41; ReturnFloat[13] = mat._42; ReturnFloat[14] = mat._43; ReturnFloat[15] = mat._44;

	return ReturnFloat;
}

void GUIView::Update()
{
	//Begin MainMenu
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Show All", NULL, _showAll))
		{
			if (_showAll)
			{
				_showAll = false;
				_showAssetSection = false;
				_showLoadedAsset = false;
				_showScene = false;
				_showModelSection = false;
				_showInspector = false;
				_showBoneHierarchy = false;
				_showAnimation = false;
			}
			else
			{
				_showAll = true;
				_showAssetSection = true;
				_showLoadedAsset = true;
				_showScene = true;
				_showModelSection = true;
				_showInspector = true;
				_showBoneHierarchy = true;
				_showAnimation = true;
			}
		}

		//----------------------
		ImGui::Separator();
		//----------------------

		ImGui::MenuItem("(Asset)", NULL, false, false);

		//----------------------
		ImGui::Separator();
		//----------------------

		if (ImGui::MenuItem("Section...", NULL, _showAssetSection))
		{
			if (_showAssetSection)
			{
				_showAssetSection = false;
				_showLoadedAsset = false;
				_showScene = false;
			}
			else
			{
				_showAssetSection = true;
				_showLoadedAsset = true;
				_showScene = true;
			}
		}

		if (ImGui::MenuItem("Loaded AssetList", NULL, _showLoadedAsset))
		{
			if (_showLoadedAsset)
			{
				_showLoadedAsset = false;
			}
			else
			{
				_showLoadedAsset = true;
			}
		}

		if (ImGui::MenuItem("Scene", NULL, _showScene))
		{
			if (_showScene)
			{
				_showScene = false;
			}
			else
			{
				_showScene = true;
			}
		}

		//----------------------
		ImGui::Separator();
		//----------------------

		ImGui::MenuItem("(Model & Effect)", NULL, false, false);

		//----------------------
		ImGui::Separator();
		//----------------------

		if (ImGui::MenuItem("Section...", NULL, _showModelSection))
		{
			if (_showModelSection)
			{
				_showModelSection = false;
				_showInspector = false;
				_showBoneHierarchy = false;
			}
			else
			{
				_showModelSection = true;
				_showInspector = true;
				_showBoneHierarchy = true;
			}
		}

		if (ImGui::MenuItem("Inspector", NULL, _showInspector))
		{
			if (_showInspector)
			{
				_showInspector = false;
			}
			else
			{
				_showInspector = true;
			}
		}

		if (ImGui::MenuItem("BoneHierarchy", NULL, _showBoneHierarchy))
		{
			if (_showBoneHierarchy)
			{
				_showBoneHierarchy = false;
			}
			else
			{
				_showBoneHierarchy = true;
			}
		}

		//----------------------
		ImGui::Separator();
		//----------------------

		ImGui::MenuItem("(Animation)", NULL, false, false);

		//----------------------
		ImGui::Separator();
		//----------------------

		if (ImGui::MenuItem("Animation", NULL, _showAnimation))
		{
			if (_showAnimation)
			{
				_showAnimation = false;
			}
			else
			{
				_showAnimation = true;
			}
		}

		//End MainMenu
		ImGui::EndMenu();
	}

	ButtonManage();
}

void GUIView::Render()
{


	//LoadedAsset
	{
		LoadedAsset();
	}

	//Scene
	{
		Scene();
	}

	//Inspector
	{
		Inspector();
	}

	//BoneHierarchy
	{
		BoneHierarchy();
	}

	//Animation
	{
		Animation();
	}
}
