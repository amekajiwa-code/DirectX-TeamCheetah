#include "pch.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	
	if (_instance == nullptr)
		_instance = new SceneManager();

	return _instance;
	
}

void SceneManager::Update()
{
	if (_currentScene == nullptr)
		return;
	_currentScene->FixedUpdate();
	_currentScene->Update();
	_currentScene->LateUpdate();
}
