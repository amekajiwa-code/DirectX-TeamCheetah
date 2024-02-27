#pragma once

#include "ServerPacketHandler.h"

enum class AIState
{
	None,
	Stand,
	Walk,
	Run,
	Damaged,
	Death,
	Battle,
	Attack,
	Ability1,
	Ability2,
	End
};

class GameServerAI
{
public:
	void Update();
private:
	bool CalcNextBehavior();
	bool IsOverlap(const Vec3& position);

	float range = 60.0f;
	AIState state = AIState::None;
};