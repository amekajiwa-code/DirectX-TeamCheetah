#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	MANAGER_SCENE()->Init();
	MANAGER_SCENE()->LoadScene(L"Test");

	MANAGER_INPUT()->Init(_hwnd);
	MANAGER_TIME()->Init();
}

void Game::Update()
{
	MANAGER_TIME()->Update();
	MANAGER_INPUT()->Update();

	GRAPHICS()->RenderBegin();
	{
		MANAGER_SCENE()->Update();
	}
	GRAPHICS()->RenderEnd();
}

void Game::Render()
{

}
