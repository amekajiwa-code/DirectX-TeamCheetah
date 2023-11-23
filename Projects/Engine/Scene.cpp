#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
		_gameObjects.erase(findIt);

}

void Scene::Awake()
{
	for (auto& gameObj : _gameObjects)
	{
		gameObj->Awake();
	}
}

void Scene::Start()
{
	for (auto& gameObj : _gameObjects)
	{
		gameObj->Start();
	}
}

void Scene::FixedUpdate()
{
	for (auto& gameObj : _gameObjects)
	{
		gameObj->FixedUpdate();
	}
}

void Scene::Update()
{
	for (auto& gameObj : _gameObjects)
	{
		gameObj->Update();
	}
}

void Scene::LateUpdate()
{
	for (auto& gameObj : _gameObjects)
	{
		gameObj->LateUpdate();
	}
}
