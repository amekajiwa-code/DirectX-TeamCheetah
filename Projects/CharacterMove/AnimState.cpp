#include "pch.h"
#include "AnimState.h"
#include "PlayerController.h"

bool PlayerAnimIdle::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_state = PlayerUnitState::Stand;
		_playerState = _contoller.lock()->GetCurrentUnitState();

		if (_animator.lock()->GetTweenDesc().current.animIndex < 0 &&
			_animator.lock()->GetTweenDesc().next.animIndex < 0)
		{
			_animator.lock()->GetTweenDesc().current.animIndex = 0;
			_animator.lock()->SetCurrentAnimation(L"Stand");
			_animator.lock()->GetTweenDesc().ClearNextAnim();
			_animator.lock()->SetNextAnimation(L"Stand");
		}
		else if (_animator.lock()->GetTweenDesc().current.animIndex > 0)
		{
			_animator.lock()->GetTweenDesc().ClearNextAnim();
			_animator.lock()->GetTweenDesc().next.animIndex = 0;
			_animator.lock()->SetNextAnimation(L"Stand");
		}

		return true;
	}

	return false;
}

bool PlayerAnimIdle::Update()
{
	if (_contoller.lock())
	{
	}

	return false;
}

bool PlayerAnimIdle::Out()
{
	return false;
}

bool PlayerAnimFrontWalk::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimFrontWalk::Update()
{
	return false;
}

bool PlayerAnimFrontWalk::Out()
{
	return false;
}

bool PlayerAnimBackWalk::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimBackWalk::Update()
{
	return false;
}

bool PlayerAnimBackWalk::Out()
{
	return false;
}

bool PlayerAnimRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimRun::Update()
{
	return false;
}

bool PlayerAnimRun::Out()
{
	return false;
}

bool PlayerAnimBackRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimBackRun::Update()
{
	return false;
}

bool PlayerAnimBackRun::Out()
{
	return false;
}

bool PlayerAnimJumpStart::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimJumpStart::Update()
{
	return false;
}

bool PlayerAnimJumpStart::Out()
{
	return false;
}

bool PlayerAnimJumpFall::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimJumpFall::Update()
{
	return false;
}

bool PlayerAnimJumpFall::Out()
{
	return false;
}

bool PlayerAnimJumpEnd::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimJumpEnd::Update()
{
	return false;
}

bool PlayerAnimJumpEnd::Out()
{
	return false;
}

bool PlayerAnimJumpEndRun::Enter(const shared_ptr<PlayerController>& playerController)
{
	return false;
}

bool PlayerAnimJumpEndRun::Update()
{
	return false;
}

bool PlayerAnimJumpEndRun::Out()
{
	return false;
}

