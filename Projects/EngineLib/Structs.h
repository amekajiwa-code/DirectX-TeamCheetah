#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "Types.h"

struct CGameDesc
{
	//Sample or Root Game Scene Pointer
	std::shared_ptr<class IExecute> App = nullptr;
	//Program Name
	std::wstring AppName = L"Default";
	//Win Size
	float width = 800.f;
	float height = 600.f;
	//WIN API
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	bool windowed = true;
	//VSync(수직동기화)
	bool vsync = false;
	//BackBuffer Clear Color
	Color clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
};
