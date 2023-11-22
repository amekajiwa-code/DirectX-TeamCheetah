#pragma once
#include "GameObject.h"

class Game
{
private:
	HWND					_hwnd;
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

