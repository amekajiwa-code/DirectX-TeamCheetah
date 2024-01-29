#pragma once

#include "GameSession.h"
#include "ServerPacketHandler.h"

#include <random>
#include <cfloat>

class GameSession;

using GameSessionRef = std::shared_ptr<GameSession>;

class GameSessionManager
{
public:
	void Add(GameSessionRef session);
	void Remove(GameSessionRef session);
	void Broadcast(SendBufferRef sendBuffer);
	Set<GameSessionRef> GetSessionsRef() { return _sessions; }
	//플레이어
	map<uint64, Player_INFO> GetUserInfoList() { return _userInfoList; }
	void UpdateUserInfo(Player_INFO info);
	//몬스터
	void GenerateMobList();
	map<uint64, MONSTER_INFO> GetMobInfoList() { return _mobInfoList; }
	void UpdateMobInfo(MONSTER_INFO info);
	//AI
	DirectX::XMFLOAT3 CalcNextPos(MONSTER_INFO chara);
private:
	USE_LOCK;
	Set<GameSessionRef> _sessions;
private:
	uint64 sessionIdCount = 0;
private:
	map<uint64, MONSTER_INFO> _mobInfoList;
	map<uint64, Player_INFO> _userInfoList;
};

extern GameSessionManager GSessionManager;
