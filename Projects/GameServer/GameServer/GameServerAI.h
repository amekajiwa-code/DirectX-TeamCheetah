#pragma once

#include "ServerPacketHandler.h"

class GameServerAI
{
public:
	void Update();
private:
	bool CalcNextBehavior();

	float range = 60.0f;
};