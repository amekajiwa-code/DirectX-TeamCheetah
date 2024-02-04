#pragma once

class GameObject;
class Terrain;

class Scene
{
public:
	virtual void Init();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();

	virtual void Add(shared_ptr<GameObject> object);
	virtual void Remove(shared_ptr<GameObject> object);

	unordered_set<shared_ptr<GameObject>> GetObjects() { return _objects; }
	shared_ptr<GameObject> GetCamera() { return _cameras.empty() ? nullptr : *_cameras.begin(); }
	shared_ptr<GameObject> GetLight() { return _lights.empty() ? nullptr : *_lights.begin(); }
	shared_ptr<Terrain> GetCurrentTerrain() { return _terrain==nullptr ? nullptr:_terrain; };
	void SetTerrain(shared_ptr<Terrain> terrain) { _terrain = terrain; };
private:
	unordered_set<shared_ptr<GameObject>> _objects;
	// Cache Camera
	unordered_set<shared_ptr<GameObject>> _cameras;
	// Cache Light
	unordered_set<shared_ptr<GameObject>> _lights;

	shared_ptr<Terrain> _terrain;
};
