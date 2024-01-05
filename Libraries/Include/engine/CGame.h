#pragma once

class CGame
{
public:
	CGame(){}
	virtual ~CGame(){}
protected:
	CGameDesc _desc;
	DWORD _dwStyle;
protected:
	virtual void Update();
protected:
	BOOL InitInstance(int cmdShow);
	virtual ATOM MyRegisterClass();
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual WPARAM Run(CGameDesc& desc);
};

