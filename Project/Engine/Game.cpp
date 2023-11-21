#include "pch.h"
#include "Game.h"
#include "Camera.h"

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
	{
		_object->GetOrAddTransform();
	}
	_pipeline = make_shared<Pipeline>();
	_camera = make_shared<GameObject>();
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update()
{
	_object->Update();
	_camera->Update();
}

void Game::Render()
{
	GRAPHICS()->RenderBegin();
	{
		_object->Render(_pipeline);
	}
	GRAPHICS()->RenderEnd();
}
