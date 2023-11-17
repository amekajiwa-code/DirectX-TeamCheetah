#pragma once

#include "Types.h"
#include "Values.h"
#include "Struct.h"

//STL
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

//STD
#include <string>
#include <memory>

//WINAPI
#include <Windows.h>
#include <assert.h>
using namespace std;

//DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <dxtex/DirectXTex.h>
#include <dxtex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

//Lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#ifdef _DEBUG
#pragma comment(lib, "dxtex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "dxtex\\DirectXTex.lib")
#endif // _DEBUG

//Extern
extern HWND g_hWnd;

//Engine
#include "Graphics.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"

//Macro
#define CHECK(p)	assert(SUCCEEDED(p))
#define GRAPHICS()	Graphics::GetInstance()

