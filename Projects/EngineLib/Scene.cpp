#include "pch.h"
#include "Terrain.h"
#include "Scene.h"
void Scene::Init() {};

void Scene::Start()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;

	for (shared_ptr<GameObject> object : objects)
	{
		object->Start();
	}
}
void Scene::FixedUpdate()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;

	for (shared_ptr<GameObject> object : objects)
	{
		object->FixedUpdate();
	}

}
void Scene::Update()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;

	for (shared_ptr<GameObject> object : objects)
	{
		object->Update();
	}

}

void Scene::LateUpdate()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;

	for (shared_ptr<GameObject> object : objects)
	{
		object->LateUpdate();
	}
	// INSTANCING
	vector<shared_ptr<GameObject>> temp;
	temp.insert(temp.end(), objects.begin(), objects.end());
	MANAGER_INSTANCING()->Render(temp);
}
void Scene::ShadowUpdate()
{
	unordered_set<shared_ptr<GameObject>> objects = _shadowobjects;

	vector<shared_ptr<GameObject>> temp;
	temp.insert(temp.end(), objects.begin(), objects.end());
	MANAGER_INSTANCING()->Render(temp);
}
void Scene::Add(shared_ptr<GameObject> object)
{
	_objects.insert(object);

	if (object->GetCamera() != nullptr)
	{
		_cameras.insert(object);
	}

	if (object->GetLight() != nullptr)
	{
		_lights.insert(object);
	}
}
void Scene::AddShadow(shared_ptr<GameObject> object)
{
	_shadowobjects.insert(object);

}
void Scene::Remove(shared_ptr<GameObject> object)
{
	_objects.erase(object);

	_cameras.erase(object);

	_lights.erase(object);
}
