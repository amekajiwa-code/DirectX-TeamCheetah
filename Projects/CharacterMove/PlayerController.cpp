#include "pch.h"
#include "PlayerController.h"
#include <float.h>
#include "AnimState.h"

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

	//앞
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		_speed = 300.f;
		_moveForward = _transform.lock()->GetLookVector();

		_movePos += _moveForward * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}
	//뒤
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		_speed = 150.f;
		_moveForward = _transform.lock()->GetLookVector();

		_movePos -= _moveForward * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_movePos);
	}
	//오른쪽
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		{
			_moveRight = _transform.lock()->GetRightVector();
			_movePos -= _moveRight * _speed * MANAGER_TIME()->GetDeltaTime();
			_transform.lock()->SetPosition(_movePos);
		}
	}
	//왼쪽
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		{
			_moveRight = _transform.lock()->GetRightVector();
			_movePos += _moveRight * _speed * MANAGER_TIME()->GetDeltaTime();
			_transform.lock()->SetPosition(_movePos);
		}
	}

	PlayerJump();
}

void PlayerController::PlayerJump()
{
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

	if (_isJump)
	{
		if (_isJumpUP)
		{
			if (_movePos.y <= _jumpUpMaxPos.y)
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpUpDir * _jumpPower), 1.5f * _dt);
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

			if (_movePos.y <= _jumpPower/2.0f +1.0f)
			{
				_isJumpFall = false;
				_isJumEnd = true;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 1.5f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
		if (_isJumEnd)
		{
			//if(_prevAnimState != PlayerAnimState::JumpEndRun)
			//_currentAnimState = PlayerAnimState::JumpEndRun;

			//if (_movePos.y <= 0.5f)
			//{
			//	_movePos.y = 0.5f;
			//	_transform.lock()->SetLocalPosition(_movePos);
			//	if (_prevAnimState == PlayerAnimState::JumpEndRun)
			//		_currentAnimState = PlayerAnimState::Run;
			//	_isJumEnd = false;
			//	_isJump = false;
			//	return;
			//}
			
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 1.5f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}

		}
	}
}

bool PlayerController::SetAnimState(const PlayerAnimType& animType)
{
	switch (animType)
	{
		case PlayerAnimType::Idle:
		{
			return true;
		}break;
		case PlayerAnimType::Run:
		{
			return true;
		}break;
		case PlayerAnimType::BackRun:
		{
			return true;
		}break;
		case PlayerAnimType::JumpStart:
		{
			return true;
		}break;
		case PlayerAnimType::JumpFall:
		{
			return true;
		}break;
		case PlayerAnimType::JumpEnd:
		{
			return true;
		}break;
		case PlayerAnimType::JumpEndRun:
		{
			return true;
		}break;
	}

	return false;
}

void PlayerController::ReceiveEvent(const EventArgs& args)
{
}

void PlayerController::DispatchEvent()
{
}

void PlayerController::Awake()
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
