#pragma once

#include "Engine/PlayerController.h"
#include "engine\PlayerAnimState.h"

struct CHARACTER_INFO
{
	//wstring _name;
	uint32 _hp = 1000;
	uint16 _atk = 100;
	//uint16 _def = 100;
	uint16 _moveSpeed = 10;
	uint16 _aggroLevel = 100;
	float _attackRange = 15.0f;
	Vec3 _pos = { 0.0f, 0.0f, 0.0f };
	Vec3 _Rotate = { 0.f, 0.f, 0.f };
	bool _isAlive = false;
	bool _isAttack = false;
	double _timeStamp = 0.0f;
};

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