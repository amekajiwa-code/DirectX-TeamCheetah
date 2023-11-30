#pragma once

class CGame
{
public:
	CGame(){}
	~CGame(){}
private:
	CGameDesc _desc;
private:
	void Update();
private:
	BOOL InitInstance(int cmdShow);
	ATOM MyRegisterClass();
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
public:
	WPARAM Run(CGameDesc& desc);
};

