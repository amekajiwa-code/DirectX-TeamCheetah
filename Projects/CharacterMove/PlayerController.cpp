#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::CameraMove()
{

	_dt = MANAGER_TIME()->GetDeltaTime();

	if (MANAGER_INPUT()->GetButton(KEY_TYPE::LBUTTON))
	{
		//shared_ptr<Transform> tf =
		_camRotation = _camera.lock()->GetTransform()->GetLocalRotation();

		float deltaX = _currentMousePos.x - _prevMousePos.x;
		_camRotation.y -= deltaX * _dt * 0.075f;

		//_camRotation.x = (std::max<float>(std::min(_camRotation.x, 90.0f), -90.0f));
		_camera.lock()->GetTransform()->SetLocalRotation(_camRotation);
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::RBUTTON))
	{
		
	}
}

void PlayerController::PlayerInput()
{
	if (MANAGER_INPUT()->GetButtonUp(KEY_TYPE::W))
	{

	}
	else if (MANAGER_INPUT()->GetButtonUp(KEY_TYPE::S))
	{

	}
	else if (MANAGER_INPUT()->GetButtonUp(KEY_TYPE::A))
	{

	}
	else if (MANAGER_INPUT()->GetButtonUp(KEY_TYPE::D))
	{

	}

	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		_pos = _transform.lock()->GetPosition();
		_look = _transform.lock()->GetLookVector();

		_pos += _look * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		_pos = _transform.lock()->GetPosition();
		_look = _transform.lock()->GetLookVector();

		_pos -= _look * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		_pos = _transform.lock()->GetPosition();
		_right = _transform.lock()->GetRightVector();

		_pos -= _right * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		_pos = _transform.lock()->GetPosition();
		_right = _transform.lock()->GetRightVector();

		_pos += _right * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
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
