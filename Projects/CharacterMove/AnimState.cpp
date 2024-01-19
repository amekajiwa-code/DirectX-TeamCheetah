#include "pch.h"
#include "AnimState.h"
#include "PlayerController.h"

bool PlayerAnimIdle::Enter(const shared_ptr<PlayerController>& playerController)
{
	_contoller = playerController;

	if (_contoller.lock())
	{
		_animator = _contoller.lock()->GetAnimator();
		_animType = PlayerAnimType::Idle;

		if (_animator.lock()->GetTweenDesc().current.animIndex < 0 &&
			_animator.lock()->GetTweenDesc().next.animIndex < 0)
		{
			_animator.lock()->GetTweenDesc().ClearCurrentAnim();
			_animator.lock()->GetTweenDesc().current.animIndex = 0;
			_animator.lock()->GetTweenDesc().ClearNextAnim();
		}
		else if (_animator.lock()->GetTweenDesc().current.animIndex > 0)
		{
			_animator.lock()->GetTweenDesc().ClearNextAnim();
			_animator.lock()->GetTweenDesc().next.animIndex = 0;
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
