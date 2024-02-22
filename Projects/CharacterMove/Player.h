#pragma once
#include "Character.h"

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