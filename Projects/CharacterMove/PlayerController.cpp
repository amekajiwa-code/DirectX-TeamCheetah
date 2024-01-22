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

void PlayerController::AnimStateInit()
{
	//Idle
	_animStateList.push_back(make_shared<PlayerAnimIdle>());
	//FrontRun
	_animStateList.push_back(make_shared<PlayerAnimRun>());
	//BackRun
	_animStateList.push_back(make_shared<PlayerAnimBackRun>());
	//FrontWalk
	_animStateList.push_back(make_shared<PlayerAnimFrontWalk>());
	//BackWalk
	_animStateList.push_back(make_shared<PlayerAnimBackWalk>());
	//JumpStart
	_animStateList.push_back(make_shared<PlayerAnimJumpStart>());
	//JumpFall
	_animStateList.push_back(make_shared<PlayerAnimJumpFall>());
	//JumpEnd
	_animStateList.push_back(make_shared<PlayerAnimJumpEnd>());
	//JumpEndRun
	_animStateList.push_back(make_shared<PlayerAnimJumpEndRun>());

	_animState = _animStateList[0];
	_animState->Enter(shared_from_this());
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
	KeyStateCheck();
	//Debug
	{
		string outputString;

		switch (_currentState)
		{
		case PlayerUnitState::Stand:
		{
			outputString = "Stand";
		}
		break;
		case PlayerUnitState::FrontMove:
		{
			outputString = "FrontMove";
		}
		break;
		case PlayerUnitState::FrontRightMove:
		{
			outputString = "FrontRightMove";
		}
		break;
		case PlayerUnitState::FrontLeftMove:
		{
			outputString = "FrontLeftMove";
		}
		break;
		case PlayerUnitState::BackMove:
		{
			outputString = "BackMove";
		}
		break;
		case PlayerUnitState::BackRightMove:
		{
			outputString = "BackRightMove";
		}
		break;
		case PlayerUnitState::BackLeftMove:
		{
			outputString = "BackLeftMove";
		}
		break;
		case PlayerUnitState::RightMove:
		{
			outputString = "RightMove";
		}
		break;
		case PlayerUnitState::LeftMove:
		{
			outputString = "LeftMove";
		}
		break;
		case PlayerUnitState::Jump:
		{
			outputString = "Jump";
		}
		break;
		}
		outputString += "\n";
		::OutputDebugStringA(outputString.c_str());
	}
}

void PlayerController::PlayerMove()
{
	_dt = MANAGER_TIME()->GetDeltaTime();
	_movePos = _transform.lock()->GetPosition();

	//왼쪽
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{

		_currentState = PlayerUnitState::LeftMove;

		{
			_moveRight = _transform.lock()->GetRightVector();

			if (!MANAGER_INPUT()->GetButton(KEY_TYPE::S))
			{
				_movePos -= _moveRight * _runSpeed * _dt;
			}
			else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
			{
				_movePos -= _moveRight * _walkSpeed * _dt;
			}

			_transform.lock()->SetPosition(_movePos);
		}
	}
	//오른쪽
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{

		_currentState = PlayerUnitState::RightMove;

		{
			_moveRight = _transform.lock()->GetRightVector();

			if (!MANAGER_INPUT()->GetButton(KEY_TYPE::S))
			{
				_movePos += _moveRight * _runSpeed * _dt;
			}
			else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
			{
				_movePos += _moveRight * _walkSpeed * _dt;
			}

			_transform.lock()->SetPosition(_movePos);
		}
	}

	//앞
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		_currentState = PlayerUnitState::FrontMove;

		_moveForward = _transform.lock()->GetLookVector();
		_movePos += _moveForward * _runSpeed * _dt;
		_transform.lock()->SetPosition(_movePos);

	}
	//뒤
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		_currentState = PlayerUnitState::BackMove;

		_moveForward = _transform.lock()->GetLookVector();
		_movePos -= _moveForward * _walkSpeed * _dt;
		_transform.lock()->SetPosition(_movePos);
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
			if (_movePos.y <= _jumpUpMaxPos.y + FLT_EPSILON)
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpUpDir * _jumpPower), 2.0f * _dt);
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

			if (_movePos.y <= _jumpPower / 2.0f + 1.0f)
			{
				_isJumpFall = false;
				_isJumEnd = true;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 2.0f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
		if (_isJumEnd)
		{
			if (_movePos.y <= 0.5f + FLT_EPSILON)
			{
				_movePos.y = 0.5f;
				_transform.lock()->SetLocalPosition(_movePos);
				_isJumEnd = false;
				_isJump = false;
				return;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 2.0f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
	}
}

void PlayerController::KeyStateCheck()
{
	if (!MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::A) &&
		!MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		_currentState = PlayerUnitState::Stand;
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
		MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		_currentState = PlayerUnitState::FrontLeftMove;
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
		MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		_currentState = PlayerUnitState::BackLeftMove;
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
		MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		_currentState = PlayerUnitState::FrontRightMove;
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
		MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		_currentState = PlayerUnitState::BackRightMove;
	}
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

	AnimStateInit();
}

void PlayerController::FixedUpdate()
{
	PlayerInput();
}

void PlayerController::Update()
{
	_animState->Update();
}

void PlayerController::LateUpdate()
{
	CameraMove();
}
