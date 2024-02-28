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
	virtual void ShadowUpdate();
public:
	virtual void Add(shared_ptr<GameObject> object);
	virtual void AddShadow(shared_ptr<GameObject> object);
	virtual void Remove(shared_ptr<GameObject> object);
public:
	unordered_set<shared_ptr<GameObject>> GetObjects() { return _objects; }
	unordered_set<shared_ptr<GameObject>> GetShadowObjects() { return _shadowobjects; }
	shared_ptr<GameObject> GetCamera() { return _cameras.empty() ? nullptr : *_cameras.begin(); }
	shared_ptr<GameObject> GetLight() { return _lights.empty() ? nullptr : *_lights.begin(); }
	shared_ptr<Terrain> GetCurrentTerrain() { return _terrain==nullptr ? nullptr:_terrain; };
	void SetTerrain(shared_ptr<Terrain> terrain) { _terrain = terrain; };
	shared_ptr<GameObject> Pick(int32 screenX, int32 screenY);
	wstring GetSceneName() { return _sceneName; }
	void SetSceneName(wstring sceneName) { _sceneName = sceneName; }
protected:
	wstring _sceneName;
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_set<shared_ptr<GameObject>> _shadowobjects;
	// Cache Camera
	unordered_set<shared_ptr<GameObject>> _cameras;
	// Cache Light
	unordered_set<shared_ptr<GameObject>> _lights;
	
	shared_ptr<Terrain> _terrain;
};

