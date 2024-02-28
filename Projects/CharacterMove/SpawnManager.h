#pragma once

#include "Spawner.h"

class SpawnManager : public GameObject
{
public:
	static SpawnManager& GetInstance()
	{
		static SpawnManager _instance;
		return _instance;
	}
	
public:
	void Init();
	void Update();
public:
	void AddSceneSpawner(wstring name);
	void Reset(wstring name);
	uint32 GetSpawnMapId();
	void EraseSpawnerMap(wstring name) { _spawnerMap.erase(name); }
private:
	SpawnManager() = default;
	~SpawnManager() = default;

	map<wstring, shared_ptr<Spawner>> _spawnerMap;
};