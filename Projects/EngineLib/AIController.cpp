#include "pch.h"
#include "AIController.h"

void AIController::InitAnimState()
{
	switch (_type)
	{
	case AIType::PlayableUnit:
	{
		//Idle
		_playerAnimStateList.push_back(make_shared<PlayerAnimIdle>());
		//FrontWalk
		_playerAnimStateList.push_back(make_shared<PlayerAnimFrontWalk>());
		//BackWalk
		_playerAnimStateList.push_back(make_shared<PlayerAnimBackWalk>());
		//FrontRun
		_playerAnimStateList.push_back(make_shared<PlayerAnimFrontRun>());
		//BackRun
		_playerAnimStateList.push_back(make_shared<PlayerAnimBackRun>());
		//JumpStart
		_playerAnimStateList.push_back(make_shared<PlayerAnimJumpStart>());
		//JumpFall
		_playerAnimStateList.push_back(make_shared<PlayerAnimJumpFall>());
		//JumpEnd
		_playerAnimStateList.push_back(make_shared<PlayerAnimJumpEnd>());
		//JumpEndRun
		_playerAnimStateList.push_back(make_shared<PlayerAnimJumpEndRun>());

		_currentPlayerAnimState = _playerAnimStateList[0];
		_currentPlayerAnimState->Enter(shared_from_this());
	}break;
	case AIType::EnemyUnit:
	{
		//Stand
		_enemyAnimStateList.push_back(make_shared<EnemyAnimStand>());
		//Walk
		_enemyAnimStateList.push_back(make_shared<EnemyAnimWalk>());
		//Run
		_enemyAnimStateList.push_back(make_shared<EnemyAnimRun>());
		//Damaged
		_enemyAnimStateList.push_back(make_shared<EnemyAnimDamaged>());
		//Death
		_enemyAnimStateList.push_back(make_shared<EnemyAnimDeath>());
		//Battle
		_enemyAnimStateList.push_back(make_shared<EnemyAnimBattle>());
		//Attack1
		_enemyAnimStateList.push_back(make_shared<EnemyAnimAttack1>());
		//Attack2
		_enemyAnimStateList.push_back(make_shared<EnemyAnimAttack2>());
		//Casting
		_enemyAnimStateList.push_back(make_shared<EnemyAnimCasting>());
		//Ability1
		_enemyAnimStateList.push_back(make_shared<EnemyAnimAbility1>());
		//Ability2
		_enemyAnimStateList.push_back(make_shared<EnemyAnimAbility2>());

		//Default Stand
		_currentEnemyAnimState = _enemyAnimStateList[0];
		_currentEnemyAnimState->Enter(shared_from_this());
	}break;
	}


}

bool AIController::SetAnimState(const PlayerAnimType& type)
{
	if (type == PlayerAnimType::None)
	{
		return false;
	}
	else
	{
		_currentPlayerAnimState->Out();
		_currentPlayerAnimState = _playerAnimStateList[static_cast<int>(type)];

		if (_currentPlayerAnimState)
		{
			_currentPlayerAnimState->Enter(shared_from_this());
			return true;
		}

	}

	return false;
}

bool AIController::SetAnimState(const EnemyAnimType& type)
{
	if (type == EnemyAnimType::None)
	{
		return false;
	}
	else
	{
		_currentEnemyAnimState->Out();
		_currentEnemyAnimState = _enemyAnimStateList[static_cast<int>(type)];
		if (_currentEnemyAnimState)
		{
			_currentEnemyAnimState->Enter(shared_from_this());
			return true;
		}
	}

	return false;
}

void AIController::Start()
{
	{
		_transform = GetGameObject()->GetTransform();
		_animator = GetGameObject()->GetChildByName(L"Model")->GetModelAnimator();
		_jumpState = make_shared<JumpFlag>();
	}
	switch (_type)
	{
	case AIType::PlayableUnit:
	{
		_currentPlayerState = make_shared<PlayerUnitState>();
		*_currentPlayerState = PlayerUnitState::FrontMove;
	}break;
	case AIType::EnemyUnit:
	{
		_currentEnemyState = make_shared<EnemyUnitState>();
		*_currentEnemyState = EnemyUnitState::Stand;
	}break;
	}

	InitAnimState();
}

void AIController::FixedUpdate()
{
}

void AIController::Update()
{
	switch (_type)
	{
	case AIType::PlayableUnit:
	{
		_currentPlayerAnimState->Update();
	}
		break;
	case AIType::EnemyUnit:
	{
		_currentEnemyAnimState->Update();
	}
		break;
	}
}

void AIController::LateUpdate()
{
}
