#pragma once

struct CHARACTER_INFO
{
	//wstring _name;
	//uint32 _hp;
	//uint16 _atk;
	uint16 _moveSpeed = 10.0f;
	//uint16 _attackSpeed;
	//uint16 _attackRange;
	uint16 _aggroLevel = 100;
	Vec3 _pos;
	Vec3 _Rotate = { 0.f, 0.f, 0.f };
	PlayerAnimState _animState = PlayerAnimState::Idle;
	bool _isAlive = false;
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