#pragma once
#include "Terrain.h"
class HeightGetter : public MonoBehaviour
{
private:
	Terrain* _terrain;
public: 
	float _height = 0.0f;

public:
	void Set(Terrain* terrain) { _terrain = terrain; }
	void GetHeight();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
};

