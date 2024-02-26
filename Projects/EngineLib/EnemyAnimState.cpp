#include "pch.h"
#include "EnemyAnimState.h"
#include "CharacterController.h"
#include "AIController.h"

bool EnemyAnimStand::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Stand;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Stand");

		return true;
	}

	return false;
}

bool EnemyAnimStand::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Walk:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Walk);
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Run);
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Damaged);
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Battle);
			return true;
		}break;
		case EnemyUnitState::Attack:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Attack1);
			return true;
		}break;
		}
	}

	return false;
}

bool EnemyAnimStand::Out()
{
	return false;
}

bool EnemyAnimWalk::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Walk;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Walk");

		return true;
	}

	return false;
}

bool EnemyAnimWalk::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Stand);
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Run);
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Damaged);
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Battle);
			return true;
		}break;
		}
	}

	return false;
}

bool EnemyAnimWalk::Out()
{
	return false;
}

bool EnemyAnimRun::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Run;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Run");

		return true;
	}

	return false;
}

bool EnemyAnimRun::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Stand);
			return true;
		}break;
		case EnemyUnitState::Walk:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Walk);
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Damaged);
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Battle);
			return true;
		}break;
		case EnemyUnitState::Attack:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Attack1);
			return true;
		}
		}
	}

	return false;
}

bool EnemyAnimRun::Out()
{
	return false;
}

bool EnemyAnimDamaged::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Damaged;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Damaged");

		return true;
	}

	return false;
}

bool EnemyAnimDamaged::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Stand);
			return true;
		}break;
		case EnemyUnitState::Walk:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Walk);
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Run);
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Battle);
			return true;

		}break;
		case EnemyUnitState::Attack:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Attack1);
			return true;
		}break;
		}
	}

	return false;
}

bool EnemyAnimDamaged::Out()
{
	return false;
}

bool EnemyAnimDeath::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Death;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Death");

		return true;
	}

	return false;
}

bool EnemyAnimDeath::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			return true;
		}break;
		case EnemyUnitState::Walk:
		{
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			return true;

		}break;
		}
	}

	return false;
}

bool EnemyAnimDeath::Out()
{
	return false;
}

bool EnemyAnimBattle::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Battle;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Battle");

		return true;
	}

	return false;
}

bool EnemyAnimBattle::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			return true;
		}break;
		case EnemyUnitState::Walk:
		{
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Attack:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Attack1);
			return true;
		}break;
		case EnemyUnitState::Ability1:
		{
			return true;
		}break;
		case EnemyUnitState::Ability2:
		{
			return true;
		}break;
		}
	}

	return false;
}

bool EnemyAnimBattle::Out()
{
	return false;
}

bool EnemyAnimAttack1::Enter(const shared_ptr<CharacterController>& enemyController)
{
	_controller = dynamic_pointer_cast<AIController>(enemyController);

	if (_controller.lock())
	{
		_animator = _controller.lock()->GetAnimator();
		_state = _controller.lock()->GetCurrentEnemyUnitState();
		_animType = EnemyAnimType::Attack1;

		_animator.lock()->GetTweenDesc().ClearNextAnim();
		_animator.lock()->SetNextAnimation(L"Attack1");
		return true;
	}

	return false;
}

bool EnemyAnimAttack1::Update()
{
	if (_controller.lock())
	{
		switch (*_state.lock())
		{
		case EnemyUnitState::Stand:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Stand);
			return true;
		}break;
		case EnemyUnitState::Walk:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Walk);
			return true;
		}break;
		case EnemyUnitState::Run:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Run);
			return true;
		}break;
		case EnemyUnitState::Damaged:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Damaged);
			return true;
		}break;
		case EnemyUnitState::Death:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Death);
			return true;
		}break;
		case EnemyUnitState::Battle:
		{
			_controller.lock()->SetAnimState(EnemyAnimType::Battle);
			return true;
		}break;
		}
	}

	return false;
}

bool EnemyAnimAttack1::Out()
{
	return false;
}

bool EnemyAnimCasting::Enter(const shared_ptr<CharacterController>& enemyController)
{
	return false;
}

bool EnemyAnimCasting::Update()
{
	return false;
}

bool EnemyAnimCasting::Out()
{
	return false;
}

bool EnemyAnimAttack2::Enter(const shared_ptr<CharacterController>& enemyController)
{
	return false;
}

bool EnemyAnimAttack2::Update()
{
	return false;
}

bool EnemyAnimAttack2::Out()
{
	return false;
}

bool EnemyAnimAbility1::Enter(const shared_ptr<CharacterController>& enemyController)
{
	return false;
}

bool EnemyAnimAbility1::Update()
{
	return false;
}

bool EnemyAnimAbility1::Out()
{
	return false;
}

bool EnemyAnimAbility2::Enter(const shared_ptr<CharacterController>& enemyController)
{
	return false;
}

bool EnemyAnimAbility2::Update()
{
	return false;
}

bool EnemyAnimAbility2::Out()
{
	return false;
}
