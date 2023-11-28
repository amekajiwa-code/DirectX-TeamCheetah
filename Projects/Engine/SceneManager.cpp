#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Animator.h"

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
			camera->AddComponent(make_shared<Camera>());
			scene->AddGameObject(camera);
		}
	}
	//background
	{
		//shared_ptr<GameObject> _object = make_shared<GameObject>();
		//_object->AddComponent(make_shared<MeshRenderer>());

		//wstring _key = L"Rectangle";
		//auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(_key);
		//_object->GetMeshRenderer()->SetMesh(mesh);

		//auto material = MANAGER_RESOURCES()->GetResource<Material>(L"DefaultM");
		//_object->GetMeshRenderer()->SetMaterial(material);

		//scene->AddGameObject(_object);
	}
	//monster
	{
		shared_ptr<GameObject> snake = make_shared<GameObject>();

		auto meshRenderer = make_shared<MeshRenderer>();
		snake->AddComponent(meshRenderer);
		wstring key = L"Rectangle";
		auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(key);
		meshRenderer->SetMesh(mesh);
		wstring mKey = L"DefaultM";
		auto material = MANAGER_RESOURCES()->GetResource<Material>(mKey);
		meshRenderer->SetMaterial(material);
		auto animator = make_shared<Animator>();
		snake->AddComponent(animator);
		auto anim = MANAGER_RESOURCES()->GetResource<Animation>(L"SnakeAnim");
		animator->SetAnimation(anim);

		scene->AddGameObject(snake);
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
