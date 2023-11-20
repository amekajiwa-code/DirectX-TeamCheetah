#pragma once

class Game
{
private:
	HWND					_hwnd;
	shared_ptr<Pipeline>	_pipeline;
	shared_ptr<GameObject>	_object;
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
};

