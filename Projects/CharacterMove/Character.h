#pragma once

#include "Engine/PlayerController.h"
#include "engine\PlayerAnimState.h"

class Character : public GameObject
{
public:
	Character() {};
	virtual ~Character() {};
public:
	//virtual void Update() override;
	Vec3 _prePos;
private:
	float _dt = 0.0f;
	float _interp = 1.0f;
	CHARACTER_INFO _info;
};