#include "pch.h"
#include "Terrain.h"
#include "Scene.h"
#include "BaseCollider.h"

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
	MANAGER_SHADOW()->Render(temp);
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

shared_ptr<GameObject> Scene::Pick(int32 screenX, int32 screenY)
{
	auto camera = GetCamera()->GetCamera();

	float viewportWidth = GRAPHICS()->GetViewport().GetWidth();
	float viewportHeight = GRAPHICS()->GetViewport().GetHeight();

	Matrix viewMatrix = camera->GetViewMatrix();
	Matrix viewMatrixInv = viewMatrix.Invert();
	Matrix projMatrix = camera->GetProjectionMatrix();

	float viewX = (2.f * screenX / viewportWidth - 1.f) / projMatrix(0, 0);
	float viewY = (-2.f * screenY / viewportHeight + 1.f) / projMatrix(1, 1);

	const auto& objects = GetObjects();

	float minDist = FLT_MAX;
	shared_ptr<GameObject> picked;

	for (auto& gameobject : objects)
	{
		if (gameobject->GetCollider() == nullptr)
			continue;
		else
		{
			Vec4 rayOrigin = Vec4(0.f, 0.f, 0.f, 1.f);
			Vec4 rayDir = Vec4(viewX, viewY, 1.f, 0.f);

			Vec3 worlRayOrigin = ::XMVector3TransformCoord(rayOrigin, viewMatrixInv);
			Vec3 worldRayDir = ::XMVector3TransformNormal(rayDir, viewMatrixInv);
			worldRayDir.Normalize();

			Ray ray = Ray(worlRayOrigin, worldRayDir);
			float distance = 0.f;

			if (gameobject->GetCollider()->Intersects(ray, OUT distance) == false)
				continue;

			if (distance < minDist)
			{
				minDist = distance;
				picked = gameobject;
			}
		}
	}

	return picked;
}
