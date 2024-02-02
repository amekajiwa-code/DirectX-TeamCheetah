#include "pch.h"
#include "main.h"
#include "engine/CGame.h"
#include "Demo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameDesc desc;
	desc.AppName = L"JCharacterTool";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 1280.f;
	desc.height = 720.f;
	desc.clearColor = Color(0.7f, 0.7f, 0.7f, 1.f);
	desc.App = make_shared<Demo>();

	CGame* game = new CGame();

	game->Run(desc);
	 
	delete game;
	game = nullptr;
	std::quick_exit(0);
	return 0;
}