#pragma once
#include "Character.h"

struct MONSTER_INFO : public CHARACTER_INFO
{
	uint64 _instanceId = 0;
	Vec3 _targetPos = { 0.f, 0.f, 0.f };
	bool _isMove = false;
	EnemyUnitState _animState = EnemyUnitState::Stand;
};

class Monster : Character
{
	Monster() {};
	virtual ~Monster() {};
private:
	MONSTER_INFO _mobInfo;
};

