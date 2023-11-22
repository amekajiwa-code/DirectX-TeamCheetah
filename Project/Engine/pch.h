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

//DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace Microsoft::WRL;

//Lib Header
#include <assimp/Importer.hpp>
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
#else
//DX
#pragma comment(lib, "dxtex\\DirectXTex.lib")
#pragma comment(lib, "dxtk\\DirectXTK.lib")
//Assimp
#pragma comment(lib, "assimp\\assimp-vc143-mt.lib")
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
#include "Shader.h"
#include "ConstantBuffer.h"
#include "RasterizerState.h"
#include "Texture.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Pipeline.h"
#include "Transform.h"
#include "SceneManager.h"

//Macro
#define PI			3.14159f /2
#define CHECK(p)		assert(SUCCEEDED(p))
#define GRAPHICS()	Graphics::GetInstance()
#define MANAGER_SCENE() SceneManager::GetInstance()

#ifdef _DEBUG
#define RESOURCES_ADDR_TOP L"../../Resources/"
#define RESOURCES_ADDR_SHADER L"../../Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"../../Resources/Texture/"
#define RESOURCES_ADDR_SOUND L"../../Resources/Sound/"
#else
#define RESOURCES_ADDR L"Resources/"
#define RESOURCES_ADDR_SHADER L"Resources/Shader/"
#define RESOURCES_ADDR_TEXTURE L"Resources/Texture/"
#define RESOURCES_ADDR_SOUND L"Resources/Sound/"
#endif
