#pragma once

class Scene;

class SceneManager
{
private:
	static SceneManager* _instance;
public:
	static SceneManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();

		return _instance;
	}
private:
	SceneManager();
	~SceneManager();
private:
	shared_ptr<Scene> _activeScene;
private:
	shared_ptr<Scene> LoadTestScene();
public:
	shared_ptr<Scene> GetActiveScene() const { return _activeScene; }
public:
	void LoadScene(wstring sceneName);
public:
	void Init();
	void Update();
};

