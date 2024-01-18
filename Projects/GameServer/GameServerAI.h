#pragma once

#include "GameSessionManager.h"

class GameServerAI
{
	DirectX::XMFLOAT3 nextPos(CHARACTER_INFO chara, map<uint64, Player_INFO> _userInfoList);
};

