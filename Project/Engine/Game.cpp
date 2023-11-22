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

	MANAGER_SCENE()->LoadScene(L"Test");
}

void Game::Update()
{
	GRAPHICS()->RenderBegin();
	{
		MANAGER_SCENE()->Update();
	}
	GRAPHICS()->RenderEnd();
}

void Game::Render()
{

}
