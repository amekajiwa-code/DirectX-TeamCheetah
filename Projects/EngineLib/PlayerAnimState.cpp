#include "pch.h"
#include "PlayerAnimState.h"
#include "CharacterController.h"
#include "PlayerController.h"
#include "AIController.h"
#include "stdlib.h"
#include "time.h"
#include <float.h>

bool PlayerAnimIdle::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Stand;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Stand");

	return true;
}

bool PlayerAnimIdle::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimIdle::Out()
{
	//_animator.lock()->GetTweenDesc().ClearCurrentAnim();

	return true;
}

bool PlayerAnimFrontWalk::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::FrontWalk;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Walk");

	return true;
}

bool PlayerAnimFrontWalk::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}
			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimFrontWalk::Out()
{
	return false;
}

bool PlayerAnimBackWalk::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::BackWalk;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"BackWalk");

	return true;
}

bool PlayerAnimBackWalk::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);
			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimBackWalk::Out()
{
	return false;
}

bool PlayerAnimFrontRun::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::FrontRun;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"FrontRun");

	return true;
}

bool PlayerAnimFrontRun::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;

		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}
		}
	}

	return false;
}

bool PlayerAnimFrontRun::Out()
{
	return false;
}

bool PlayerAnimBackRun::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::BackRun;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"BackRun");

	return true;
}

bool PlayerAnimBackRun::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed()+ FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimBackRun::Out()
{
	return false;
}

bool PlayerAnimJumpStart::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();

	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
		_jumpState = _aiContoller.lock()->GetJumpState();

	}

	_stateAnim = PlayerAnimType::JumpStart;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"JumpStart");

	return true;
}

bool PlayerAnimJumpStart::Update()
{
	if (_contoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJumpFall)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::JumpFall);
				return true;
			}
		}
	}
	else if (_aiContoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJumpFall)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpFall);
				return true;
			}
		}
	}

	return false;
}

bool PlayerAnimJumpStart::Out()
{
	return false;
}

bool PlayerAnimJumpFall::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
		_jumpState = _aiContoller.lock()->GetJumpState();
	}

	_stateAnim = PlayerAnimType::JumpFall;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"JumpFall");

	return true;
}

bool PlayerAnimJumpFall::Update()
{
	if (_contoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJumEnd)
			{

				_contoller.lock()->SetAnimState(PlayerAnimType::JumpEnd);

				return true;
			}
		}
	}
	else if (_aiContoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJumEnd)
			{

				_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpEnd);

				return true;
			}
		}
	}

	return false;
}

bool PlayerAnimJumpFall::Out()
{
	return false;
}

bool PlayerAnimJumpEnd::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
		_jumpState = _aiContoller.lock()->GetJumpState();
	}

	_stateAnim = PlayerAnimType::JumpEnd;
	_animator.lock()->GetTweenDesc().ClearCurrentAnim();
	_animator.lock()->SetCurrentAnimation(L"JumpEnd");
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"JumpEnd");

	return true;
}

bool PlayerAnimJumpEnd::Update()
{
	if (_contoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJump == false)
			{
				switch (*_playerState.lock())
				{
				case PlayerUnitState::Stand:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
					return true;
				}break;
				case PlayerUnitState::FrontMove:
				case PlayerUnitState::FrontRightMove:
				case PlayerUnitState::FrontLeftMove:
				case PlayerUnitState::RightMove:
				case PlayerUnitState::LeftMove:
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
						return true;
					}
				}break;
				case PlayerUnitState::BackMove:
				case PlayerUnitState::BackRightMove:
				case PlayerUnitState::BackLeftMove:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
					return true;
				}break;
				case PlayerUnitState::Stun:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
					return true;
				}break;
				case PlayerUnitState::Loot:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
					return true;
				}break;
				case PlayerUnitState::Death:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Death);
					return true;
				}break;
				case PlayerUnitState::Battle:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
					return true;
				}break;
				}
			}
		}
	}
	else if (_aiContoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJump == false)
			{
				switch (*_playerState.lock())
				{
				case PlayerUnitState::Stand:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
					return true;
				}break;
				case PlayerUnitState::FrontMove:
				case PlayerUnitState::FrontRightMove:
				case PlayerUnitState::FrontLeftMove:
				case PlayerUnitState::RightMove:
				case PlayerUnitState::LeftMove:
				{
					if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
					{
						_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
					{
						_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
						return true;
					}
				}break;
				case PlayerUnitState::BackMove:
				case PlayerUnitState::BackRightMove:
				case PlayerUnitState::BackLeftMove:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
					return true;
				}break;
				case PlayerUnitState::Stun:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
					return true;
				}break;
				case PlayerUnitState::Loot:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
					return true;
				}break;
				case PlayerUnitState::Death:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
					return true;
				}break;
				case PlayerUnitState::Battle:
				{
					_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
					return true;
				}break;
				}
			}
		}
	}

	return false;
}

bool PlayerAnimJumpEnd::Out()
{
	return false;
}

bool PlayerAnimStun::Enter(const shared_ptr<CharacterController>& playerController)
{
	return false;
}

bool PlayerAnimStun::Update()
{
	return false;
}

bool PlayerAnimStun::Out()
{
	return false;
}

bool PlayerAnimLoot::Enter(const shared_ptr<CharacterController>& playerController)
{
	return false;
}

bool PlayerAnimLoot::Update()
{
	return false;
}

bool PlayerAnimLoot::Out()
{
	return false;
}

bool PlayerAnimDamaged::Enter(const shared_ptr<CharacterController>& playerController)
{
	return false;
}

bool PlayerAnimDamaged::Update()
{
	return false;
}

bool PlayerAnimDamaged::Out()
{
	return false;
}

bool PlayerAnimDeath::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}


	_stateAnim = PlayerAnimType::Death;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Death");
	
	return false;
}

bool PlayerAnimDeath::Update()
{
	return false;
}

bool PlayerAnimDeath::Out()
{
	return false;
}

bool PlayerAnimBattle::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Battle;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Battle");

	return false;
}

bool PlayerAnimBattle::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Jump:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::JumpStart);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Attack:
		{
			::srand(time(NULL));

			int selectAttack = rand() % 2;

			if (selectAttack == 0)
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack1);

			}
			else
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::Attack2);
			}

			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimBattle::Out()
{
	return false;
}

bool PlayerAnimAttack1::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Attack1;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Attack1");
	_animator.lock()->SetFrameEnd(false);

	return false;
}

bool PlayerAnimAttack1::Update()
{
	if (_contoller.lock())
	{
		if (_animator.lock()->GetFrameEnd() == true)
		{
			_contoller.lock()->SetIsAttack(false);
		}

		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;
		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;

		}
	}
	else if (_aiContoller.lock())
	{
		if (_animator.lock()->GetFrameEnd() == true)
		{
			_aiContoller.lock()->SetIsAttack(false);
		}

		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;

		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimAttack1::Out()
{
	return true;
}

bool PlayerAnimAttack2::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Attack2;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Attack2");
	_animator.lock()->SetFrameEnd(false);

	return false;
}

bool PlayerAnimAttack2::Update()
{
	if (_contoller.lock())
	{
		if (_animator.lock()->GetFrameEnd() == true)
		{
			_contoller.lock()->SetIsAttack(false);
		}

		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Stun:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;

		case PlayerUnitState::Ability1:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		}
	}
	else if (_aiContoller.lock())
	{
		if (_animator.lock()->GetFrameEnd() == true)
		{
			_aiContoller.lock()->SetIsAttack(false);
		}

		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stand);
			return true;
		}break;
		case PlayerUnitState::Battle:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Battle);
			return true;
		}break;
		case PlayerUnitState::FrontMove:
		case PlayerUnitState::FrontRightMove:
		case PlayerUnitState::FrontLeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::RightMove:
		case PlayerUnitState::LeftMove:
		{
			if (_aiContoller.lock()->GetCurrentSpeed() < _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_aiContoller.lock()->GetCurrentSpeed() + FLT_EPSILON >= _aiContoller.lock()->GetDefaultSpeed())
			{
				_aiContoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::Stun:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Stun);
			return true;
		}break;
		case PlayerUnitState::Loot:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Loot);
			return true;
		}break;
		case PlayerUnitState::Death:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Death);
			return true;
		}break;

		case PlayerUnitState::Ability1:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability1);
			return true;
		}break;
		case PlayerUnitState::Ability2:
		{
			_aiContoller.lock()->SetAnimState(PlayerAnimType::Ability2);
			return true;
		}break;
		}
	}

	return false;
}

bool PlayerAnimAttack2::Out()
{
	return true;
}

bool PlayerAnimCasting::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Casting;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Casting");

	return false;
}

bool PlayerAnimCasting::Update()
{
	return false;
}

bool PlayerAnimCasting::Out()
{
	return false;
}

bool PlayerAnimAbility1::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Ability1;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Ability1");

	return false;
}

bool PlayerAnimAbility1::Update()
{
	return false;
}

bool PlayerAnimAbility1::Out()
{
	return false;
}

bool PlayerAnimAbility2::Enter(const shared_ptr<CharacterController>& playerController)
{
	if (dynamic_pointer_cast<PlayerController>(playerController))
	{
		_contoller = dynamic_pointer_cast<PlayerController>(playerController);
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
	}
	else
	{
		_aiContoller = dynamic_pointer_cast<AIController>(playerController);
		_animator = _aiContoller.lock()->GetAnimator();
		_playerState = _aiContoller.lock()->GetCurrentPlayerUnitState();
	}

	_stateAnim = PlayerAnimType::Ability2;
	_animator.lock()->GetTweenDesc().ClearNextAnim();
	_animator.lock()->SetNextAnimation(L"Ability2");

	return false;
}

bool PlayerAnimAbility2::Update()
{
	return false;
}

bool PlayerAnimAbility2::Out()
{
	return false;
}
