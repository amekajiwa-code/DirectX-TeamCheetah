#pragma once
#include "engine/CGame.h"

class ToolWindows : public CGame
{
public:
	ToolWindows();
	virtual ~ToolWindows();
protected:
	virtual void Update() override;
	static LRESULT CALLBACK CustomWndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	virtual ATOM MyRegisterClass() override;
public:
	virtual WPARAM Run(CGameDesc& desc) override;
};

