#pragma once
#define _CRT_SECURE_NO_WARNINGS

//Default
#include "Types.h"
#include "Values.h"
#include "Struct.h"

//STL
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <string>
#include <filesystem>

//WINAPI
#include <Windows.h>
#include <assert.h>
using namespace std;

//Utils
#include "tinyxml2.h"
using namespace tinyxml2;

//DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace Microsoft::WRL;

//Lib Header
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/ImGuiFileDialog.h>
#include <dxtex/DirectXTex.h>
#include <dxtex/DirectXTex.inl>

//Lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#ifdef _DEBUG
//DX
#pragma comment(lib, "dxtex\\DirectXTex_debug.lib")
#pragma comment(lib, "dxtk\\DirectXTK_debug.lib")
//Assimp
#pragma comment(lib, "assimp\\assimp-vc143-mtd.lib")
//Imgui
#pragma comment(lib, "imgui\\Imgui_debug.lib")
#else
//DX
#pragma comment(lib, "dxtex\\DirectXTex.lib")
#pragma comment(lib, "dxtk\\DirectXTK.lib")
//Assimp
#pragma comment(lib, "assimp\\assimp-vc143-mt.lib")
//Imgui
#pragma comment(lib, "imgui\\Imgui.lib")
#endif

//Extern
extern HWND g_hWnd;

//Engine
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexData.h"
#include "ShaderBase.h"
#include "ConstantBuffer.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Pipeline.h"
#include "Transform.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

//Macro
#define PI			3.14159f / 2.0f
#define CHECK(p)	assert(SUCCEEDED(p))
#define GRAPHICS()	Graphics::GetInstance()
#define WTM(p) string(p.begin(), p.end())
#define MTW(p) wstring(p.begin(), p.end()) 
//Manager
#define MANAGER_SCENE()		SceneManager::GetInstance()
#define MANAGER_INPUT()		InputManager::GetInstance()
#define MANAGER_TIME()		TimeManager::GetInstance()
#define MANAGER_RESOURCES() ResourceManager::GetInstance()
#define MANAGER_RENDERER()	RenderManager::GetInstance()

#ifdef _DEBUG
//resources
#define RESOURCES_ADDR_TOP L"../../Resources/"
#define RESOURCES_ADDR_SHADER L"../../Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"../../Resources/Texture/"
#define RESOURCES_ADDR_SPRITE L"../../Resources/Sprite/"
#define RESOURCES_ADDR_SOUND L"../../Resources/Sound/"
//data
#define DATA_ADDR_SCREENSHOT L"../../Data/ScreenShot/"
#define DATA_ADDR_ANIMATION L"../../Data/Resources/Animation/"
#else
//resources
#define RESOURCES_ADDR_TOP L"Resources/"
#define RESOURCES_ADDR_SHADER L"Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"Resources/Texture/"
#define RESOURCES_ADDR_SPRITE L"Resources/Sprite/"
#define RESOURCES_ADDR_SOUND L"Resources/Sound/"
//data
#define DATA_ADDR_SCREENSHOT L"Data/ScreenShot/"
#define DATA_ADDR_ANIMATION L"Data/Resources/Animation/"
#endif

#include "Utils.h"
