#include "pch.h"
#include "ToolWindows.h"
#include "engine/IExecute.h"
#include "ImGuiManager.h"


ToolWindows::ToolWindows()
{
}

ToolWindows::~ToolWindows()
{
}

void ToolWindows::Update()
{
	MANAGER_TIME()->Update();
	MANAGER_INPUT()->Update();

	GRAPHICS()->RenderBegin();
	MANAGER_IMGUI()->Update();
	_desc.App->Update();
	_desc.App->Render();
	MANAGER_IMGUI()->Render();
	GRAPHICS()->RenderEnd();

}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
 
LRESULT ToolWindows::CustomWndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle, message, wParam, lParam);
	}
}

ATOM ToolWindows::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CustomWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _desc.hInstance;
	wcex.hIcon = ::LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _desc.AppName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

WPARAM ToolWindows::Run(CGameDesc& desc)
{
	_desc = desc;
	assert(_desc.App != nullptr);

	// 1) 윈도우 창 정보 등록
	MyRegisterClass();

	// 2) 윈도우 창 생성
	if (!InitInstance(SW_SHOWNORMAL))
		return FALSE;
	//Global
	g_hWnd = _desc.hWnd;
	g_gameDesc = _desc;
	//Manager Init
	GRAPHICS()->Init();
	MANAGER_TIME()->Init();
	MANAGER_INPUT()->Init();
	MANAGER_IMGUI()->Init();
	//Scene Init
	_desc.App->Init();

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			Update();
		}
	}

	return msg.wParam;
}
