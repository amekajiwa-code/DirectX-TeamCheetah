#include "pch.h"
#include "CGame.h"
#include "IExecute.h"
#include "ImGuiManager.h"

HWND g_hWnd = 0;
CGameDesc g_gameDesc;

void CGame::Update()
{
	MANAGER_TIME()->Update();
	MANAGER_INPUT()->Update();

	ShowFps();

	GRAPHICS()->RenderBegin();
	MANAGER_IMGUI()->Update(); //IMGUI
	MANAGER_SCENE()->Update();
	//_desc.App->Update();
	//_desc.App->Render();
	MANAGER_IMGUI()->Render(); //IMGUI
	GRAPHICS()->RenderEnd();
}

BOOL CGame::InitInstance(int cmdShow)
{
	RECT windowRect = { 0, 0, _desc.width, _desc.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	//_dwStyle = WS_OVERLAPPED | WS_SYSMENU;
	_dwStyle = WS_OVERLAPPEDWINDOW;
	
	_desc.hWnd = CreateWindowW(_desc.AppName.c_str(), _desc.AppName.c_str(), _dwStyle,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, _desc.hInstance, nullptr);

	if (!_desc.hWnd)
		return FALSE;

	::ShowWindow(_desc.hWnd, cmdShow);
	::UpdateWindow(_desc.hWnd);

	return TRUE;
}

ATOM CGame::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CGame::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_SIZE:
		break;
	case WM_MOUSEWHEEL:
	{
		int rawData = GET_WHEEL_DELTA_WPARAM(wParam);

		if (rawData > 0)
		{
			g_gameDesc.WheelState = 1;
		}
		else if (rawData < 0)
		{
			g_gameDesc.WheelState = -1;
		}
		break;
	}
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle, message, wParam, lParam);
	}
}

WPARAM CGame::Run(CGameDesc& desc)
{
	_desc = desc;
	assert(_desc.App != nullptr);

	// 1) ������ â ���� ���
	MyRegisterClass();

	// 2) ������ â ����
	if (!InitInstance(SW_SHOWNORMAL))
		return FALSE;
	//Global
	g_hWnd = _desc.hWnd;
	g_gameDesc = _desc;
	//Manager Init
	GRAPHICS()->Init();
	MANAGER_TIME()->Init();
	MANAGER_INPUT()->Init();
	MANAGER_IMGUI()->Init(); //IMGUI
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
			g_gameDesc.WheelState = 0;
		}
	}

	return msg.wParam;
}

void CGame::ShowFps()
{
	uint32 fps = MANAGER_TIME()->GetFPS();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowTextW(g_gameDesc.hWnd, text);
}