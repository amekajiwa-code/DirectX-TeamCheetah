#pragma once
class Game
{
private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;
private:

public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

