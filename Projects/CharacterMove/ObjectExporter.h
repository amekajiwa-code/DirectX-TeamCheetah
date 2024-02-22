#pragma once
#include "StructList.h"

class EnemyUnit;
class CoreHound;
struct MobParser {
	pair <wstring, shared_ptr<CoreHound>> dog_pair;

};

class ObjectExporter
{
	map<wstring, std::vector<float>> enemyListforServer;
	bool isLoaded = false;
public:
	vector<shared_ptr<GameObject>> _structureList;
	vector<shared_ptr<EnemyUnit>>  _enemyList;
public:
	bool OpenFile(wstring filename);
	void LoadStructure();
	void LoadEnemies();
	map<wstring, std::vector<float>>& GetenemyListForServer() {
		return enemyListforServer;
	}
};

