#pragma once

class CharacterController;

class HeightGetter : public MonoBehaviour
{
private:
	Terrain* _terrain;
	shared_ptr<CharacterController> _controller;
public: 
	float _height = 0.0f;
public:
	void Set(Terrain* terrain) { _terrain = terrain; }
	float GetHeight();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
};

