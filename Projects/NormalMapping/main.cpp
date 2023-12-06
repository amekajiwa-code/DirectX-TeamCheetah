#include "pch.h"
#include "main.h"
#include "engine/CGame.h"
#include "Demo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGameDesc desc;
	desc.AppName = L"TestScene";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 1600;
	desc.height = 900;
	desc.clearColor = Color(0.f, 0.f, 0.f, 0.f);
	desc.App = make_shared<Demo>();

	CGame* game = new CGame();

	game->Run(desc);
	 
	delete game;

	return 0;
}