#pragma once

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene();
private:
	vector<shared_ptr<GameObject>> _gameObjects;
public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);
public:
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
public:
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();

};

