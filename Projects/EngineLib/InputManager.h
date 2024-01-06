#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',
	M = 'M',

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',
	KEY_5 = '5',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
	F12 = VK_F12,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END),
};

class InputManager
{
private:
	InputManager();
	~InputManager(){}
private:
	static InputManager* _instance;
public:
	static InputManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new InputManager();

		return _instance;
	}
public:
	void Init();
	void Update();
public:
	// 누르고 있을 때
	bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESS; }
	// 맨 처음 눌렀을 때
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	// 맨 처음 눌렀다 뗐을 때
	bool GetButtonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }
public:
	const Vec3& GetScreenMousePos() { return _screenMousePos; }
	const Vec3& GetWorldMousePos() { return _worldMousePos; }
private:
	inline KEY_STATE GetState(KEY_TYPE key) { return _states[static_cast<uint8>(key)]; }
	void CalculateWorldPos();
private:
	HWND _hwnd;
	vector<KEY_STATE> _states;
	POINT _mousePos = {};
	Vec3 _screenMousePos;
	Vec3 _worldMousePos;
};

