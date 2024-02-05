#pragma once

#include "ServerPacketHandler.h"

class GameServerAI
{
public:
	void Start();
private:
	bool MoveAI(DirectX::XMFLOAT3 targetPos);
	bool RotateAI(DirectX::XMFLOAT3 targetPos);
	bool CalcNextBehavior();
};

