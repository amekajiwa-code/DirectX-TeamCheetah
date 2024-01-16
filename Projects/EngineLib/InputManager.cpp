#include "pch.h"
#include "InputManager.h"

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager()
{
	_hwnd = g_hWnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void InputManager::Init()
{
	_hwnd = g_hWnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void InputManager::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (_hwnd != hwnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
			_states[key] = KEY_STATE::NONE;

		return;
	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// Ű�� ���� ������ true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&_mousePos);
	::ScreenToClient(_hwnd, &_mousePos);

	//Screen pos
	{
		CalculateScreenPos();
	}
	//World Pos
	{
		CalculateWorldPos();
	}
}

void InputManager::CalculateWorldPos()
{
	float ndcX = 2.0f * _mousePos.x / g_gameDesc.width - 1.0f;
	float ndcY = -2.0f * _mousePos.y / g_gameDesc.height + 1.0f;

	Vec3 nVec(ndcX, ndcY, 1.0f);
	Matrix mat = (Camera::S_MatView).Invert();
	Vec3 last = Vec3::Transform(nVec, mat);

	_worldMousePos.x = last.x;
	_worldMousePos.y = last.y;
	_worldMousePos.z = last.z;
}

void InputManager::CalculateScreenPos()
{
	float ndcX = 2.0f * _mousePos.x / g_gameDesc.width - 1.0f;
	float ndcY = -2.0f * _mousePos.y / g_gameDesc.height + 1.0f;

	float scaleX = -g_gameDesc.width / 2 + (ndcX + 1.0f) * g_gameDesc.width / 2;
	float scaleY = -g_gameDesc.height / 2 + (ndcY + 1.0f) * g_gameDesc.height / 2;

	_screenMousePos.x = scaleX;
	_screenMousePos.y = scaleY;
}
