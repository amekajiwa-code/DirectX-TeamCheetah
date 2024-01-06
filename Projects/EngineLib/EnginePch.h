#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
//resources
#define RESOURCES_ADDR_TOP L"../../Resources/"
#define RESOURCES_ADDR_ASSET L"../../Resources/Assets/"
#define RESOURCES_ADDR_ASSET_SKELETAL L"../../Resources/Assets/Skeletal/"
#define RESOURCES_ADDR_ASSET_STATIC L"../../Resources/Assets/Static/"
#define RESOURCES_ADDR_MESH L"../../Resources/Mesh/"
#define RESOURCES_ADDR_MESH_SKELETAL L"../../Resources/Mesh/Skeletal/"
#define RESOURCES_ADDR_MESH_STATIC L"../../Resources/Mesh/Static/"
#define RESOURCES_ADDR_ANIMATION L"../../Resources/Animation/"
#define RESOURCES_ADDR_SHADER L"../../Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"../../Resources/Texture/"
#define RESOURCES_ADDR_TEXTURE_SKELETAL L"../../Resources/Texture/Skeletal/"
#define RESOURCES_ADDR_TEXTURE_STATIC L"../../Resources/Texture/Static/"
#define RESOURCES_ADDR_SPRITE L"../../Resources/Sprite/"
#define RESOURCES_ADDR_SOUND L"../../Resources/Sound/"
//data
#define DATA_ADDR_SAVE L"../../Data/Save/"
#define DATA_ADDR_LOAD L"../../Data/Load/"
#define DATA_ADDR_SCREENSHOT L"../../Data/ScreenShot/"
#else
//resources
#define RESOURCES_ADDR_TOP L"Resources/"
#define RESOURCES_ADDR_ASSET L"Resources/Assets/"
#define RESOURCES_ADDR_ASSET_SKELETAL L"Resources/Assets/Skeletal/"
#define RESOURCES_ADDR_ASSET_STATIC L"Resources/Assets/Static/"
#define RESOURCES_ADDR_MESH L"Resources/Mesh/"
#define RESOURCES_ADDR_MESH_SKELETAL L"Resources/Mesh/Skeletal/"
#define RESOURCES_ADDR_MESH_STATIC L"Resources/Mesh/Static/"
#define RESOURCES_ADDR_ANIMATION L"Resources/Animation/"
#define RESOURCES_ADDR_SHADER L"Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"Resources/Texture/"
#define RESOURCES_ADDR_TEXTURE_SKELETAL L"Resources/Texture/Skeletal/"
#define RESOURCES_ADDR_TEXTURE_STATIC L"Resources/Texture/Static/"
#define RESOURCES_ADDR_SPRITE L"Resources/Sprite/"
#define RESOURCES_ADDR_SOUND L"Resources/Sound/"
//data
#define DATA_ADDR_SAVE L"Data/Save/"
#define DATA_ADDR_LOAD L"Data/Load/"
#define DATA_ADDR_SCREENSHOT L"Data/ScreenShot/"
#endif

//Default
#include "Types.h"
#include "Structs.h"

//STL
#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

using namespace std;

//WINAPI
#include <Windows.h>
#include <assert.h>
#include <optional>

//Utils
#include "tinyxml2.h"
using namespace tinyxml2;

//DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <dxtex/DirectXTex.h>
#include <dxtex/DirectXTex.inl>
#include <fx11/d3dx11effect.h>
using namespace DirectX;
using namespace Microsoft::WRL;

//Lib Header
//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//imgui
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/ImGuiFileDialog.h>
#include <imgui/ImGuizmo.h>
#include <imgui/ImSequencer.h>
#include <imgui/ImZoomSlider.h>
#include <imgui/ImCurveEdit.h>
#include <imgui/GraphEditor.h>

//Lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#ifdef _DEBUG
//DX
#pragma comment(lib, "dxtex\\DirectXTex_d.lib")
#pragma comment(lib, "dxtk\\DirectXTK_d.lib")
#pragma comment(lib, "fx11\\Effects11d.lib")
////Assimp
#pragma comment(lib, "assimp\\assimp-vc143-mtd.lib")
////Imgui
#pragma comment(lib, "imgui\\Imgui_d.lib")
#else
//DX
#pragma comment(lib, "dxtex\\DirectXTex.lib")
#pragma comment(lib, "dxtk\\DirectXTK.lib")
#pragma comment(lib, "fx11\\Effects11.lib")
////Assimp
#pragma comment(lib, "assimp\\assimp-vc143-mt.lib")
////Imgui
#pragma comment(lib, "imgui\\Imgui.lib")
#endif

#define PI			XM_PI
#define CHECK(p)	assert(SUCCEEDED(p))

//Extern
extern HWND g_hWnd;
extern CGameDesc g_gameDesc;

#include "Graphics.h"
#define GRAPHICS()		Graphics::GetInstance()
#define DEVICE()		GRAPHICS()->GetDevice()
#define DC()			GRAPHICS()->GetDeviceContext()

//Engine
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Geometry.h"
#include "GeometryHelper.h"

//Manager
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

//Global Macro
#define MANAGER_INPUT() InputManager::GetInstance()
#define MANAGER_TIME()	TimeManager::GetInstance()
#define MANAGER_RESOURCES() ResourceManager::GetInstance()
#define MANAGER_RENDERER() RenderManager::GetInstance()

//Components
#include "Component.h"
#include "MonoBehaviour.h"

//fixed
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"

//Resources
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Model.h"

//GameObject
#include "GameObject.h"

