#pragma once
#include "Character.h"

struct MONSTER_INFO : public CHARACTER_INFO
{
	uint64 _instanceId = 0;
	Vec3 _targetPos;
};

class Monster : Character
{
	Monster() {};
	virtual ~Monster() {};
private:
	MONSTER_INFO _mobInfo;
};

