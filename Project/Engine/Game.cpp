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
	_object = make_shared<GameObject>();
	_pipeline = make_shared<Pipeline>();
}

void Game::Update()
{
	_object->Update();
}

void Game::Render()
{
	GRAPHICS()->RenderBegin();
	{
		_object->Render(_pipeline);
	}
	GRAPHICS()->RenderEnd();
}
