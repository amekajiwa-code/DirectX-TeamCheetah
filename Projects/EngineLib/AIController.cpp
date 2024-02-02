#include "pch.h"
#include "AIController.h"
#include "AnimState.h"

void AIController::InitAnimState()
{
	//Stand
	_animStateList.push_back(make_shared<EnemyAnimStand>());
	//Walk
	_animStateList.push_back(make_shared<EnemyAnimWalk>());
	//Run
	_animStateList.push_back(make_shared<EnemyAnimRun>());
	//Damaged
	_animStateList.push_back(make_shared<EnemyAnimDamaged>());
	//Death
	_animStateList.push_back(make_shared<EnemyAnimDeath>());
	//Battle
	_animStateList.push_back(make_shared<EnemyAnimBattle>());
	//Attack1
	_animStateList.push_back(make_shared<EnemyAnimAttack1>());
	//Attack2
	_animStateList.push_back(make_shared<EnemyAnimAttack2>());
	//Casting
	_animStateList.push_back(make_shared<EnemyAnimCasting>());
	//Ability1
	_animStateList.push_back(make_shared<EnemyAnimAbility1>());
	//Ability2
	_animStateList.push_back(make_shared<EnemyAnimAbility2>());

	//Default Stand
	_currentAnimState = _animStateList[0];
}

bool AIController::SetAnimState(const EnemyAnimType& type)
{
	if (type == EnemyAnimType::None)
	{
		return false;
	}
	else
	{
		_currentAnimState->Out();
		_currentAnimState = _animStateList[static_cast<int>(type)];
		if (_currentAnimState)
		{
			_currentAnimState->Enter(shared_from_this());
			return true;
		}
	}

	return false;
}

void AIController::Start()
{
	{
		_currentState = make_shared<EnemyUnitState>();
		*_currentState = EnemyUnitState::Stand;
	}

	{
		_transform = GetGameObject()->GetTransform();
		_animator = GetGameObject()->GetChildByName(L"Model")->GetModelAnimator();
	}

	InitAnimState();
}

void AIController::FixedUpdate()
{


	_currentAnimState->Update();
}

void AIController::Update()
{
}

void AIController::LateUpdate()
{
}
