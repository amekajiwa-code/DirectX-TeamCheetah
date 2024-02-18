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
		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&_mousePos);
	::ScreenToClient(_hwnd, &_mousePos);

	//{
	//	Vec3 scmPos = GetWorldMousePos(Camera::S_MatView, Camera::S_MatProjection);

	//	wstring tPos = L"X:";
	//	tPos += ::to_wstring(scmPos.x);
	//	tPos += L"  Y:";
	//	tPos += ::to_wstring(scmPos.y);
	//	tPos += L" Z:";
	//	tPos += ::to_wstring(scmPos.z);
	//	tPos += L"\n";
	//	OutputDebugString(tPos.c_str());
	//}

}

Vec3& InputManager::GetScreenMousePos()
{
	_screenMousePos.x = _mousePos.x;
	_screenMousePos.y = _mousePos.y;
	_screenMousePos.z = 0.f;

	return _screenMousePos;
}

Vec3& InputManager::GetWorldMousePos(const Matrix& view, const Matrix& projcetion)
{
	Viewport& vPort = GRAPHICS()->GetViewport();
	Vec3 mPos;
	mPos.x = _mousePos.x;
	mPos.y = _mousePos.y;
	mPos.z = 0.f;

	Vec3 rVector = vPort.UnProjcetion(mPos, Matrix::Identity, view, projcetion);
	_worldMousePos = rVector;


	//XMFLOAT3 scPos;
	//scPos.x = _mousePos.x;
	//scPos.y = _mousePos.y;
	//scPos.z = 0.f;

	//XMVECTOR worldPos = XMVector3Unproject(XMLoadFloat3(&scPos), 0, 0, vPort.GetWidth(), vPort.GetHeight(), 0.1f, 1000.f, Camera::S_MatProjection, Camera::S_MatView, Matrix::Identity);

	//_worldMousePos.x = worldPos.m128_f32[0];
	//_worldMousePos.y = worldPos.m128_f32[1];
	//_worldMousePos.z = worldPos.m128_f32[2];


	return _worldMousePos;
}