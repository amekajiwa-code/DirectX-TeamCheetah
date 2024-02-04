#pragma once
#include "Scene.h"

class SceneManager
{
	SceneManager();
	~SceneManager();
	static SceneManager* _instance;
public:
	static SceneManager* GetInstance();
public:
	void Update();

	template<typename T>
	void ChangeScene(shared_ptr<T> scene)
	{
		_currentScene = scene;
		scene->Init();
		scene->Start();	}

	shared_ptr<Scene> GetCurrentScene() { return _currentScene; }

private:
	shared_ptr<Scene> _currentScene = make_shared<Scene>();
};

