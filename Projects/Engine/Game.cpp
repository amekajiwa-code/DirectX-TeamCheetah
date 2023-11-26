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
	MANAGER_TIME()->Init();
	MANAGER_INPUT()->Init(_hwnd);
	MANAGER_RENDERER()->Init();
}

void Game::Update()
{
	MANAGER_TIME()->Update();
	MANAGER_INPUT()->Update();
	MANAGER_SCENE()->Update();
}

void Game::Render()
{
	MANAGER_RENDERER()->Update();
}
