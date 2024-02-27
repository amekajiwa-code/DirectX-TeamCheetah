#include "pch.h"
#include "PlayerController.h"
#include "PlayerAnimState.h"
#include "HeightGetter.h"
#include <float.h>
#include "CharacterInfo.h"

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
	//FrontWalk
	_animStateList.push_back(make_shared<PlayerAnimFrontWalk>());
	//BackWalk
	_animStateList.push_back(make_shared<PlayerAnimBackWalk>());
	//FrontRun
	_animStateList.push_back(make_shared<PlayerAnimFrontRun>());
	//BackRun
	_animStateList.push_back(make_shared<PlayerAnimBackRun>());
	//JumpStart
	_animStateList.push_back(make_shared<PlayerAnimJumpStart>());
	//JumpFall
	_animStateList.push_back(make_shared<PlayerAnimJumpFall>());
	//JumpEnd
	_animStateList.push_back(make_shared<PlayerAnimJumpEnd>());
	//Stun
	_animStateList.push_back(make_shared<PlayerAnimStun>());
	//Loot
	_animStateList.push_back(make_shared<PlayerAnimLoot>());
	//Damaged
	_animStateList.push_back(make_shared<PlayerAnimDamaged>());
	//Death
	_animStateList.push_back(make_shared<PlayerAnimDeath>());
	//Battle
	_animStateList.push_back(make_shared<PlayerAnimBattle>());
	//Attack1
	_animStateList.push_back(make_shared<PlayerAnimAttack1>());
	//Attack2
	_animStateList.push_back(make_shared<PlayerAnimAttack2>());
	//Casting
	_animStateList.push_back(make_shared<PlayerAnimCasting>());
	//Ability1
	_animStateList.push_back(make_shared<PlayerAnimAbility1>());
	//Ability2
	_animStateList.push_back(make_shared<PlayerAnimAbility2>());

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

			_camera.lock()->GetTransform()->RotateAround(_camRot);
		}
	}

	//마우스 오른쪽 버튼 누르고 있을 때(캐릭터회전 = 카메라 회전(위치이동))
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::RBUTTON) && _isAlive == true)
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

bool PlayerController::SetAnimState(const PlayerAnimType& animType)
{
	if (animType == PlayerAnimType::None)
	{
		return false;
	}
	else
	{
		_animState->Out();

		_animState = _animStateList[static_cast<int>(animType)];

		if (_animState)
		{
			_animState->Enter(shared_from_this());
			return true;
		}

	}

	return false;
}

const PlayerAnimType& PlayerController::GetCurrentAnimType()
{
	return _animState->GetStateAnimtype();
}

void PlayerController::PlayerInput()
{
	if (_isAlive == true)
	{
		PlayerMove();
	}

	_animState->Update();


	//Debug
	{
		string outputString;

		switch (*_currentState)
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

	if (_heightGetterCom.lock())
	{
		if (_jumpState->isJump == false)
			_movePos.y = _heightGetterCom.lock()->GetHeight();
	}

	if (_isSlow)
	{
		_currentSpeed = _slowSpeed;
	}
	else
	{
		_currentSpeed = _defaultSpeed;
	}

	PlayerPicking();
	PlayerAttack();

	if (_isAttack == false)
	{
		//왼쪽
		if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
		{
			*_currentState = PlayerUnitState::LeftMove;
			{
				_moveRight = _transform.lock()->GetRightVector();
				_movePos -= _moveRight * _currentSpeed * _dt;
				_transform.lock()->SetPosition(_movePos);
			}
		}
		//오른쪽
		else if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
		{
			*_currentState = PlayerUnitState::RightMove;

			{
				_moveRight = _transform.lock()->GetRightVector();
				_movePos += _moveRight * _currentSpeed * _dt;
				_transform.lock()->SetPosition(_movePos);
			}
		}

		//앞
		if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
		{
			*_currentState = PlayerUnitState::FrontMove;

			_moveForward = _transform.lock()->GetLookVector();
			_movePos += _moveForward * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);

		}
		//뒤
		else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
		{
			*_currentState = PlayerUnitState::BackMove;

			_moveForward = _transform.lock()->GetLookVector();
			_movePos -= _moveForward * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);
		}
	}
	else // _isAttack == true
	{
		//왼쪽
		if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
		{
			_moveRight = _transform.lock()->GetRightVector();
			_movePos -= _moveRight * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);
		}
		//오른쪽
		else if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
		{
			_moveRight = _transform.lock()->GetRightVector();
			_movePos += _moveRight * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);
		}

		//앞
		if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
		{
			_moveForward = _transform.lock()->GetLookVector();
			_movePos += _moveForward * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);
		}
		//뒤
		else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
		{
			_moveForward = _transform.lock()->GetLookVector();
			_movePos -= _moveForward * _currentSpeed * _dt;
			_transform.lock()->SetPosition(_movePos);
		}
	}

	if (_isAttack == false)
	{
		PlayerJump();
	}

	KeyStateCheck();
}

void PlayerController::PlayerJump()
{

	//점프
	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::SPACE))
	{
		if (!_jumpState->isJump)
		{
			_jumpState->isJump = true;
			_jumpState->isJumpUP = true;
			_jumpUpMaxPos = _movePos + (_jumpUpDir * _jumpPower);
			*_currentState = PlayerUnitState::Jump;
		}
	}

	if (_jumpState->isJump)
	{
		if (_jumpState->isJumpUP)
		{
			if (_movePos.y < _jumpUpMaxPos.y + FLT_EPSILON)
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpUpDir * _jumpPower), 2.0f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
			else
			{
				_jumpState->isJumpUP = false;
				_jumpState->isJumpFall = true;
			}
		}
		if (_jumpState->isJumpFall)
		{
			float height = _heightGetterCom.lock()->GetHeight();
			float test = height + _jumpPower;
			if (_movePos.y < (height + _jumpPower) / 1.4f)
			{
				_jumpState->isJumpFall = false;
				_jumpState->isJumEnd = true;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 1.5f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
		if (_jumpState->isJumEnd)
		{
			if (_movePos.y < _heightGetterCom.lock()->GetHeight() + FLT_EPSILON)
			{
				_movePos.y = _heightGetterCom.lock()->GetHeight();
				_transform.lock()->SetLocalPosition(_movePos);
				_jumpState->isJumEnd = false;
				_jumpState->isJump = false;
				return;
			}
			else
			{
				_movePos = Vec3::Lerp(_movePos, Vec3(_movePos + _jumpDownDir * _jumpPower), 1.5f * _dt);
				_transform.lock()->SetPosition(_movePos);
			}
		}
	}
}

void PlayerController::PlayerAttack()
{
	if (_isAttack == true && _jumpState->isJump == false && _isPicked == true)
	{
		_battleTimer = 0.f;
		*_currentState = PlayerUnitState::Attack;
	}
}

void PlayerController::PlayerSpawn()
{
	_isAlive = true;
	_transform.lock()->SetLocalPosition(_spawnPos);
	_playerInfoCom.lock()->Reset();

	MANAGER_IMGUI()->NotifyPlayerAlive(true);
}

void PlayerController::PlayerDeath()
{
	_isAlive = false;
	SetAnimState(PlayerAnimType::Death);

	MANAGER_IMGUI()->NotifyPlayerAlive(false);
}

void PlayerController::PlayerPicking()
{
	if (_isPicked)
	{
		_pickedInfo = _pickedObj->GetComponent<CharacterInfo>()->GetCharacterInfo();
		MANAGER_IMGUI()->UpdatePicked(true, _pickedInfo._maxHp, _pickedInfo._hp, _pickedObj->GetName());
		if (_pickedInfo._hp == 0)
		{
			MANAGER_IMGUI()->UpdatePicked(false);
			_isPicked = false;
			//MANAGER_SCENE()->GetCurrentScene()->Remove(_pickedObj);
		}

		if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::RBUTTON))
		{
			int32 mx = MANAGER_INPUT()->GetScreenMousePos().x;
			int32 my = MANAGER_INPUT()->GetScreenMousePos().y;

			auto pickObj = MANAGER_SCENE()->GetCurrentScene()->Pick(mx, my);

			if (pickObj && pickObj->GetName() != L"") //어떤 타입이든 인식할수 있게 수정해야할 필요 있음
			{
				Vec3 diff = DirectX::XMVectorSubtract(_movePos, _pickedInfo._pos);
				float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(diff));

				if (distance <= 15.0f)
				{
					if (_isAttack == false)
					{
						_attackQueue.push(_pickedInfo);
					}
					_isAttack = true;
					_isBattle = true;
				}
				
			}
		}
	}
	
	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::LBUTTON))
	{
		int32 mx = MANAGER_INPUT()->GetScreenMousePos().x;
		int32 my = MANAGER_INPUT()->GetScreenMousePos().y;

		auto pickObj = MANAGER_SCENE()->GetCurrentScene()->Pick(mx, my);

		if (pickObj && pickObj->GetName() != L"") //어떤 타입이든 인식할수 있게 수정해야할 필요 있음
		{
			_isPicked = true;
			_pickedObj = pickObj;
		}
		else
		{
			MANAGER_IMGUI()->UpdatePicked(false);
			_isPicked = false;
		}
	}
}

void PlayerController::KeyStateCheck()
{
	if (_jumpState->isJump == false)
	{
		if (_isAttack == false)
		{
			if (*_currentState == PlayerUnitState::LeftMove ||
				*_currentState == PlayerUnitState::RightMove ||
				*_currentState == PlayerUnitState::FrontMove)
			{
				_isSlow = false;
			}
			else if (*_currentState == PlayerUnitState::BackMove)
			{
				_isSlow = true;
			}

			if (MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
				MANAGER_INPUT()->GetButton(KEY_TYPE::A))
			{
				*_currentState = PlayerUnitState::FrontLeftMove;
			}
			else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
				MANAGER_INPUT()->GetButton(KEY_TYPE::A))
			{
				_isSlow = true;
				*_currentState = PlayerUnitState::BackLeftMove;
			}
			else if (MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
				MANAGER_INPUT()->GetButton(KEY_TYPE::D))
			{
				*_currentState = PlayerUnitState::FrontRightMove;
			}
			else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
				MANAGER_INPUT()->GetButton(KEY_TYPE::D))
			{
				_isSlow = true;
				*_currentState = PlayerUnitState::BackRightMove;
			}
			else if (!MANAGER_INPUT()->GetButton(KEY_TYPE::W) &&
				!MANAGER_INPUT()->GetButton(KEY_TYPE::S) &&
				!MANAGER_INPUT()->GetButton(KEY_TYPE::A) &&
				!MANAGER_INPUT()->GetButton(KEY_TYPE::D))
			{

				if (_isBattle)
				{
					_currentSpeed = _defaultSpeed;
					*_currentState = PlayerUnitState::Battle;
				}
				else
				{
					_currentSpeed = _defaultSpeed;
					*_currentState = PlayerUnitState::Stand;
				}

			}
		}

	}
}

void PlayerController::NotifyPlayerAlive(bool isAlive)
{
	_isAlive = isAlive;

	if (isAlive == true)
	{
		SetAnimState(PlayerAnimType::Stand);
	}
	
	if (isAlive == false)
	{
		SetAnimState(PlayerAnimType::Death);
	}
}

int PlayerController::GetAttackQueueSize()
{
	if (_attackQueue.empty() == false)
	{
		int queueSize = _attackQueue.size();
		_attackQueue.pop();
		return queueSize;
	}

	return -1;
}

void PlayerController::ReceiveEvent(const EventArgs& args)
{
}

void PlayerController::DispatchEvent()
{
}

void PlayerController::Start()
{
	_currentState = make_shared<PlayerUnitState>();
	*_currentState = PlayerUnitState::Stand;
	_jumpState = make_shared<JumpFlag>();

	_transform = GetGameObject()->GetTransform();
	_camera = GetGameObject()->GetChildByName(L"Camera");
	_animator = GetGameObject()->GetChildByName(L"Model")->GetModelAnimator();
	_heightGetterCom = GetGameObject()->GetComponent<HeightGetter>();
	{
		if (_transform.lock())
		{
			Vec3 temPos = _transform.lock()->GetLocalPosition();
			temPos.y = _heightGetterCom.lock()->GetHeight();
			_transform.lock()->SetLocalPosition(temPos);
		}
	}

	_rCamPos = _camera.lock()->GetTransform()->GetLocalPosition();
	_camDist = max(fabs(_rCamPos.x), fabs(_rCamPos.z));

	AnimStateInit();
}

void PlayerController::FixedUpdate()
{
	if (_isAlive)
	{
		if (_playerInfoCom.lock() == nullptr)
		{
			_playerInfoCom = GetGameObject()->GetComponent<CharacterInfo>();
		}
		else
		{
			if (_playerInfoCom.lock()->GetCharacterInfo()._hp <= 0)
			{
				PlayerDeath();
			}
		}
	}

	if (_isBattle)
	{
		if (_battleTimer + FLT_EPSILON >= _battleTime)
		{
			_isBattle = false;
		}

		_battleTimer += MANAGER_TIME()->GetDeltaTime();
	}
}

void PlayerController::Update()
{
	PlayerInput();
}

void PlayerController::LateUpdate()
{
	CameraMove();
}