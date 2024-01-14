#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

Vec3 PlayerController::QuatToEulerAngles(Quaternion q)
{
	Vec3 angle;

	//x roll
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angle.x = std::atan2(sinr_cosp, cosr_cosp);
	//y pitch
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angle.y = std::atan2(sinp, cosp) - PI;
	//z yaw
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angle.z = std::atan2(siny_cosp, cosy_cosp);

	return angle;
}

void PlayerController::CameraMove()
{
	_dt = MANAGER_TIME()->GetDeltaTime();
	_currentMousePos = MANAGER_INPUT()->GetScreenMousePos();

	//마우스 왼쪽 버튼 누르고 있을 때
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::LBUTTON))
	{

	}
	//마우스 오른쪽 버튼 누르고 있을 때
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::RBUTTON))
	{
		{
			float deltaX = _currentMousePos.x - _prevMousePos.x;
			float deltaY = _currentMousePos.y - _prevMousePos.y;

			_camRot.x = ::XMConvertToRadians(deltaY) * 10 * _dt;
			_camRot.y = ::XMConvertToRadians(deltaX) * 10 * _dt;
			_camRot.z = 0;

			_camera.lock()->GetTransform()->RotateAround(_camRot);
		}

		if( MANAGER_INPUT()->GetButton(KEY_TYPE::W) ||
			MANAGER_INPUT()->GetButton(KEY_TYPE::S) ||
			MANAGER_INPUT()->GetButton(KEY_TYPE::A) ||
			MANAGER_INPUT()->GetButton(KEY_TYPE::D))
		{
			{
				_playerRot = GetTransform()->GetLocalRotation();
				float deltaX = _currentMousePos.x - _prevMousePos.x;
				_playerRot.y += ::XMConvertToRadians(deltaX) * 10 * _dt;
				GetTransform()->SetLocalRotation(_playerRot);

				const auto& Camtransform = _camera.lock()->GetTransform();

				Matrix rFinal = Camtransform->GetWorldMatrix() * GetTransform()->GetWorldMatrix().Invert();
				Vec3 temp = { rFinal._41,rFinal._42,rFinal._43 };
				temp.x = 0;
				if (temp.z >= 0)
					temp.z = -temp.z;
				Camtransform->SetLocalPosition(temp);
			}
		}

	}

	//휠 올렸을 때
	if (g_gameDesc.WheelState == 1)
	{
		_camPos = _camera.lock()->GetTransform()->GetLocalPosition();
		if (_camPos.z <= 1000.f)
		{
			_camPos.z += _camSpeed * _dt;
			_camera.lock()->GetTransform()->SetLocalPosition(_camPos);
		}
	}
	//휠 내렸을 때
	else if (g_gameDesc.WheelState == -1)
	{
		_camPos = _camera.lock()->GetTransform()->GetLocalPosition();

		if (_camPos.z >= -1000.f)
		{
			_camPos.z -= _camSpeed * _dt;
			_camera.lock()->GetTransform()->SetLocalPosition(_camPos);
		}
	}


	_prevMousePos = _currentMousePos;
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

	//앞
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		_pos = _transform.lock()->GetPosition();
		_look = _transform.lock()->GetLookVector();

		_pos += _look * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	//뒤
	else if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		_pos = _transform.lock()->GetPosition();
		_look = _transform.lock()->GetLookVector();

		_pos -= _look * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	//왼쪽
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		_pos = _transform.lock()->GetPosition();
		_right = _transform.lock()->GetRightVector();

		_pos -= _right * _speed * MANAGER_TIME()->GetDeltaTime();
		_transform.lock()->SetPosition(_pos);
	}
	//오른쪽
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
