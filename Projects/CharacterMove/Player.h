#pragma once
#include "Character.h"

struct MESSAGE
{
	char _messageBox[50];
};

struct Player_INFO : public CHARACTER_INFO
{
	uint64 _uid;
	bool _isOnline = false;
	PlayerUnitState _animState = PlayerUnitState::Stand;
	JumpFlag _jumpFlag;
	MESSAGE _message;
};

class Player : public Character
{
public:
	Player() {};
	virtual ~Player() {};
public:
	bool CheckIsAttackAndUpdate();
private:
	float _dt = 0.0f;
	float _interp = 1.0f;
	Player_INFO _info;
};