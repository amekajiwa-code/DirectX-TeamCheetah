#include "pch.h"
#include "SpawnManager.h"

void SpawnManager::Init()
{
    wstring name = MANAGER_SCENE()->GetCurrentScene()->GetSceneName();
    SpawnManager::GetInstance().AddSceneSpawner(name);
}

void SpawnManager::Update()
{
    for (const auto& pair : _spawnerMap) {
        const std::wstring& key = pair.first;
        const std::shared_ptr<Spawner>& spawner = pair.second;

        spawner->Update();
    }
}

void SpawnManager::AddSceneSpawner(wstring name)
{
    shared_ptr<Spawner> spawner = std::make_shared<Spawner>();
    spawner->Init();
    _spawnerMap.insert(std::make_pair(name, spawner));
}

void SpawnManager::Reset(wstring name)
{
    /*const auto it = _spawnerMap.find(name);

    if (it != _spawnerMap.end())
    {
        it->second->Reset();
    }*/

    for (auto& pair : _spawnerMap) {
        pair.second->Reset();
    }
}

uint32 SpawnManager::GetSpawnMapId()
{
    wstring name = MANAGER_SCENE()->GetCurrentScene()->GetSceneName();

    if (name == L"BaseScene")
    {
        return 0;
    }

    if (name == L"DungeonScene")
    {
        return 1;
    }

    
}

