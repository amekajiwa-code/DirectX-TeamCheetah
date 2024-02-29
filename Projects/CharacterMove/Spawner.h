#pragma once

#include "Character.h"
#include "Player.h"
#include "ClientPacketHandler.h"
#include "engine\AIController.h"
#include "engine/Warrior.h"
#include "engine/CoreHound.h"
#include "engine/BaronGeddon.h"
#include "engine/CharacterInfo.h"

enum
{
	Lobby = 0,
	Dungeon = 1,
	BossRoom = 2,
};

class Spawner : public GameObject
{
public:
	Spawner() = default;
	~Spawner() = default;
public:
	void Init();
	void Update();
public:
	//플레이어
	void SpawnOtherPlayer(uint64 uid, Vec3 spawnPos);
	void SpawnOtherPlayers();
	//몬스터
	void SpawnMonster(uint64 uid, uint32 monsterId, Vec3 spawnPos);
	void SpawnMonsters();
	int GetOtherPlayersSize() { return _otherPlayers.size(); }
	void Reset();

	uint32 GetSpawnMapId() { return _spawnMapId; }
private:
	uint32 _spawnMapId = 99;
	shared_ptr<AIController> _aiCon;
	map<uint64, shared_ptr<GameObject>> _otherPlayers;
	map<uint64, shared_ptr<GameObject>> _monsters;
};