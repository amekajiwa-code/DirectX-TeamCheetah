#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	
	//camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		{
			camera->GetOrAddTransform();
			camera->AddComponent(make_shared<Camera>());
			scene->AddGameObject(camera);
		}
	}
	//background
	{
		shared_ptr<GameObject> _object = make_shared<GameObject>();
		_object->GetOrAddTransform();
		_object->AddComponent(make_shared<MeshRenderer>());
		scene->AddGameObject(_object);
	}

	return scene;
}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();

	Init();
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->FixedUpdate();
	_activeScene->Update();
	_activeScene->LateUpdate();
}
