#include "pch.h"
#include "AIController.h"

#include <float.h>

AIController::AIController()
{
}

AIController::~AIController()
{
}

void AIController::PlayerJump()
{
	if (_isJump)
	{
		if (_isJumpUP)
		{
			if (_movePos.y <= _jumpUpMaxPos.y - FLT_EPSILON)
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpUpDir * _jumpPower), 2.5f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
			else
			{
				_isJumpUP = false;
				_isJumpFall = true;
			}
		}
		if (_isJumpFall)
		{
			if (_movePos.y <= 0.5f - FLT_EPSILON)
			{
				_movePos.y = 0.5f;
				_transform.lock()->SetPosition(_movePos);
				_isJumpFall = false;
				_isJump = false;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 3.0f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
	}
}

void AIController::PlayerAnimControll()
{
	switch (_currentAnimState)
	{
	case PlayerAnimState::Idle:
		_animator.lock()->SetAnimationByName(L"Stand");
		break;
	case PlayerAnimState::FrontWalk:
		break;
	case PlayerAnimState::BackWalk:
		break;
	case PlayerAnimState::Run:
		_animator.lock()->SetAnimationByName(L"Run");
		break;
	case PlayerAnimState::BackRun:
		_animator.lock()->SetAnimationByName(L"BackRun");
		break;
	case PlayerAnimState::Stun:
		break;
	case PlayerAnimState::Loot:
		break;
	case PlayerAnimState::Death:
		break;
	case PlayerAnimState::JumpStart:
		break;
	case PlayerAnimState::JumpFall:
		break;
	case PlayerAnimState::JumpEnd:
		break;
	case PlayerAnimState::Battle:
		break;
	case PlayerAnimState::Attack1:
		break;
	case PlayerAnimState::Attack2:
		break;
	case PlayerAnimState::Casting:
		break;
	case PlayerAnimState::Ability1:
		break;
	case PlayerAnimState::Ability2:
		break;
	}
}

void AIController::ReceiveEvent(const EventArgs& args)
{
}

void AIController::DispatchEvent()
{
}

void AIController::Start()
{
	_transform = GetGameObject()->GetTransform();
	//_camera = GetGameObject()->GetChildByName(L"Camera");
	_animator = GetGameObject()->GetChildByName(L"Model")->GetModelAnimator();
}

void AIController::FixedUpdate()
{

}

void AIController::Update()
{
	PlayerAnimControll();
}

void AIController::LateUpdate()
{

}