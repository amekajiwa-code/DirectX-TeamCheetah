#include "pch.h"
#include "PlayerController.h"
#include <float.h>

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::CameraMove()
{
	_dt = MANAGER_TIME()->GetDeltaTime();
	_currentMousePos = MANAGER_INPUT()->GetScreenMousePos();

	//마우스 왼쪽 버튼 누르고 있을 때(카메라만 시점 변경)
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::LBUTTON))
	{
		{
			_rCamPos = _camera.lock()->GetTransform()->GetLocalPosition();
			_camDist = max(fabs(_rCamPos.x), fabs(_rCamPos.z));

			float deltaX = _currentMousePos.x - _prevMousePos.x;
			float deltaY = _currentMousePos.y - _prevMousePos.y;

			_camRot.x = ::XMConvertToRadians(deltaY) * 10 * _dt;
			_camRot.y = ::XMConvertToRadians(deltaX) * 10 * _dt;
			_camRot.z = ::XMConvertToRadians(_camera.lock()->GetTransform()->GetLocalRotation().z) * 10 * _dt;

			_camera.lock()->GetTransform()->RotateAround(_camRot);
		}
	}

	//마우스 오른쪽 버튼 누르고 있을 때(캐릭터회전 = 카메라 회전(위치이동))
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::RBUTTON))
	{
		{
			_playerRot = _transform.lock()->GetLocalRotation();

			float deltaX = _currentMousePos.x - _prevMousePos.x;
			_playerRot.y += ::XMConvertToRadians(deltaX) * 10 * _dt;
			_transform.lock()->SetLocalRotation(_playerRot);

			Vec3 look = _transform.lock()->GetLookVector();
			look.y = _rCamPos.y;
			look.z -= _camDist;

			_camera.lock()->GetTransform()->SetLocalPosition(look);
		}
	}

	//휠 올렸을 때(시점 앞으로)
	if (g_gameDesc.WheelState == 1)
	{
		_camPos = _camera.lock()->GetTransform()->GetLocalPosition();
		if (_camPos.z <= 1000.f)
		{
			_camPos.z += _camSpeed * _dt;
			_camera.lock()->GetTransform()->SetLocalPosition(_camPos);

			_rCamPos = _camera.lock()->GetTransform()->GetLocalPosition();
			_camDist = max(fabs(_rCamPos.x), fabs(_rCamPos.z));
		}
	}

	//휠 내렸을 때(시점 뒤로)
	else if (g_gameDesc.WheelState == -1)
	{
		_camPos = _camera.lock()->GetTransform()->GetLocalPosition();

		if (_camPos.z >= -1000.f)
		{
			_camPos.z -= _camSpeed * _dt;
			_camera.lock()->GetTransform()->SetLocalPosition(_camPos);

			_rCamPos = _camera.lock()->GetTransform()->GetLocalPosition();
			_camDist = max(fabs(_rCamPos.x), fabs(_rCamPos.z));
		}
	}

	_prevMousePos = _currentMousePos;
}

void PlayerController::PlayerInput()
{
	PlayerMove();
}

void PlayerController::PlayerMove()
{
	_movePos = _transform.lock()->GetPosition();

	PlayerJump();
	PlayerAnimControll();


	//앞
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		_currentAnimState = PlayerAnimState::Run;

		_speed = 300.f;
		_moveForward = _transform.lock()->GetLookVector();

		_movePos += _moveForward * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}
	//뒤
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		_currentAnimState = PlayerAnimState::BackRun;

		_speed = 150.f;
		_moveForward = _transform.lock()->GetLookVector();

		_movePos -= _moveForward * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}

	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		if (_currentAnimState == PlayerAnimState::Idle)
		{
			_currentAnimState = PlayerAnimState::Run;

		}
		_moveRight = _transform.lock()->GetRightVector();

		_movePos -= _moveRight * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}
	//왼쪽
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		if (_currentAnimState == PlayerAnimState::Idle)
		{
			_currentAnimState = PlayerAnimState::Run;

		}

		_moveRight = _transform.lock()->GetRightVector();

		_movePos += _moveRight * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}

	//점프
	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::SPACE))
	{
		if (!_isJump)
		{
			_isJump = true;
			_isJumpUP = true;
			_jumpUpMaxPos = _movePos + _jumpUpDir * _jumpPower;
		}
	}


	if (!MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::A) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		_currentAnimState = PlayerAnimState::Idle;
	}

	_prevAnimState = _currentAnimState;
}

void PlayerController::PlayerJump()
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

void PlayerController::PlayerAnimControll()
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

void PlayerController::ReceiveEvent(const EventArgs& args)
{
}

void PlayerController::DispatchEvent()
{
}

void PlayerController::Start()
{
	_transform = GetGameObject()->GetTransform();
	_camera = GetGameObject()->GetChildByName(L"Camera");
	_animator = GetGameObject()->GetChildByName(L"Model")->GetModelAnimator();

	_rCamPos = _camera.lock()->GetTransform()->GetLocalPosition();
	_camDist = max(fabs(_rCamPos.x), fabs(_rCamPos.z));
}

void PlayerController::FixedUpdate()
{
	PlayerInput();
}

void PlayerController::Update()
{
}

void PlayerController::LateUpdate()
{
	CameraMove();
}