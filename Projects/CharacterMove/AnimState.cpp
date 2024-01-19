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

		if (_animator.lock()->GetTweenDesc().current.animIndex != 0)
		{
			_animator.lock()->GetTweenDesc().next.animIndex = 0;
		}
		return true;
	}

	return false;
}

bool PlayerAnimIdle::Update(const shared_ptr<PlayerController>& playerController)
{
	if (_contoller.lock())
	{

		if (_animator.lock()->GetTweenDesc().current.animIndex)
		{

		}

	}

	return false;
}

bool PlayerAnimIdle::Out(const shared_ptr<PlayerController>& playerController)
{
}
