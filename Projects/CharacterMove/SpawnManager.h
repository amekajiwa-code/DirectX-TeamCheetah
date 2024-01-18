#pragma once

#include "Character.h"
#include "Player.h"
#include "ClientPacketHandler.h"

class SpawnManager : public GameObject
{
public:
	static SpawnManager& GetInstance()
	{
		static SpawnManager _instance;
		return _instance;
	}
	//플레이어
	void SpawnOtherPlayer(uint64 uid, Vec3 spawnPos);
	void SpawnOtherPlayers();
	//몬스터
	void SpawnMonsters();
	int GetOtherPlayersSize() { return _otherPlayers.size(); }
public:
	void Update();
private:
	SpawnManager() = default;
	~SpawnManager() = default;

	map<uint64, shared_ptr<Character>> _otherPlayers;
	map<uint64, shared_ptr<Character>> _monsters;
};