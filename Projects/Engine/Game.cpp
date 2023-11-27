#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	MANAGER_RESOURCES()->Init();
	MANAGER_SCENE()->Init();
	MANAGER_SCENE()->LoadScene(L"Test");

	MANAGER_TIME()->Init();
	MANAGER_INPUT()->Init();
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
