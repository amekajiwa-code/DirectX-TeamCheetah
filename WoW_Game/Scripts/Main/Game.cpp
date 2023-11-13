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
	_width = g_winSizeX;
	_height = g_winSizeY;
}

void Game::Update()
{
}

void Game::Render()
{
}
