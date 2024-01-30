#include "pch.h"
#include "AnimState.h"
#include "PlayerController.h"
#include "AIController.h"

bool PlayerAnimIdle::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_stateAnim = PlayerAnimType::Stand;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Stand");

		return true;
	}

	return false;
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
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
		}
	}

	return false;
}

bool PlayerAnimIdle::Out()
{
	_animator.lock()->GetTweenDesc().ClearNextAnim();

	return true;
}

bool PlayerAnimFrontWalk::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::FrontWalk;
		_playerState = _contoller.lock()->GetCurrentUnitState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Walk");

		return true;
	}

	return false;
}

bool PlayerAnimFrontWalk::Update()
{
	if (_contoller.lock())
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
		{
			if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
		{
			if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
			_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);
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

	return false;
}

bool PlayerAnimFrontWalk::Out()
{
	return false;
}

bool PlayerAnimBackWalk::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::BackWalk;
		_playerState = _contoller.lock()->GetCurrentUnitState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"BackWalk");

		return true;
	}

	return false;
}

bool PlayerAnimBackWalk::Update()
{
	if (_contoller.lock())
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
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::RightMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
				return true;
			}
		}break;
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
			else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
			_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);
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

	return false;
}

bool PlayerAnimBackWalk::Out()
{
	return false;
}

bool PlayerAnimFrontRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::FrontRun;
		_playerState = _contoller.lock()->GetCurrentUnitState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"FrontRun");

		return true;
	}

	return false;
}

bool PlayerAnimFrontRun::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
		}break;
		case PlayerUnitState::BackMove:
		case PlayerUnitState::BackRightMove:
		case PlayerUnitState::BackLeftMove:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::BackRun);
			return true;
		}break;
		case PlayerUnitState::RightMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
		}break;
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
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
			_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);
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

	return false;
}

bool PlayerAnimFrontRun::Out()
{
	return false;
}

bool PlayerAnimBackRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::BackRun;
		_playerState = _contoller.lock()->GetCurrentUnitState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"BackRun");

		return true;
	}

	return false;
}

bool PlayerAnimBackRun::Update()
{
	if (_contoller.lock())
	{
		switch (*_playerState.lock())
		{
		case PlayerUnitState::Stand:
		{
			_contoller.lock()->SetAnimState(PlayerAnimType::Stand);
		}break;
		case PlayerUnitState::RightMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
				return true;
			}
		}break;
		case PlayerUnitState::LeftMove:
		{
			if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
			{
				_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
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
			_contoller.lock()->SetAnimState(PlayerAnimType::Attack1);
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

	return false;
}

bool PlayerAnimBackRun::Out()
{
	return false;
}

bool PlayerAnimJumpStart::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::JumpStart;
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"JumpStart");

		return true;
	}

	return false;
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

	return false;
}

bool PlayerAnimJumpStart::Out()
{
	return false;
}

bool PlayerAnimJumpFall::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::JumpFall;
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"JumpFall");

		return true;
	}

	return false;
}

bool PlayerAnimJumpFall::Update()
{
	if (_contoller.lock())
	{
		if (_jumpState.lock())
		{
			if (_jumpState.lock()->isJumEnd)
			{
				if (*_playerState.lock() == PlayerUnitState::FrontMove ||
					*_playerState.lock() == PlayerUnitState::FrontLeftMove ||
					*_playerState.lock() == PlayerUnitState::FrontRightMove)
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::JumpEnd);

				}
				else
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::JumpEnd);

				}
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

bool PlayerAnimJumpEnd::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::JumpEnd;
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();

		_animator.lock()->GetTweenDesc().ClearCurrentAnim();
		_animator.lock()->SetCurrentAnimation(L"JumpEnd");
		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"JumpEnd");

		return true;
	}

	return false;
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
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
						return true;
					}
				}break;
				case PlayerUnitState::LeftMove:
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
				case PlayerUnitState::Battle:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
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

bool PlayerAnimJumpEndRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_stateAnim = PlayerAnimType::JumpEndRun;
		_playerState = _contoller.lock()->GetCurrentUnitState();
		_jumpState = _contoller.lock()->GetJumpState();

		_animator.lock()->GetTweenDesc().ClearCurrentAnim();
		_animator.lock()->SetCurrentAnimation(L"JumpEndRun");
		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"JumpEndRun");

		return true;
	}
	return false;
}

bool PlayerAnimJumpEndRun::Update()
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
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontRun);
						return true;
					}
				}break;
				case PlayerUnitState::LeftMove:
				{
					if (_contoller.lock()->GetCurrentSpeed() < _contoller.lock()->GetDefaultSpeed())
					{
						_contoller.lock()->SetAnimState(PlayerAnimType::FrontWalk);
						return true;
					}
					else if (_contoller.lock()->GetCurrentSpeed() >= _contoller.lock()->GetDefaultSpeed())
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
				case PlayerUnitState::Battle:
				{
					_contoller.lock()->SetAnimState(PlayerAnimType::Battle);
					return true;
				}break;
				}
			}
		}
	}

	return false;
}

bool PlayerAnimJumpEndRun::Out()
{
	return false;
}

