#include "pch.h"
#include "CameraMove.h"

void CameraMove::Start()
{
}

void CameraMove::Update()
{
	_dt = MANAGER_TIME()->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();

	//translate
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::W))
	{
		pos += GetTransform()->GetLookVector() * _speed * _dt;
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::S))
	{
		pos -= GetTransform()->GetLookVector() * _speed * _dt;
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::A))
	{
		pos -= GetTransform()->GetRightVector() * _speed * _dt;
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::D))
	{
		pos += GetTransform()->GetRightVector() * _speed * _dt;
	}

	GetTransform()->SetPosition(pos);

	//rotate
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::Q))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.x += _dt * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::E))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.x -= _dt * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::Z))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.y += _dt * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (MANAGER_INPUT()->GetButton(KEY_TYPE::C))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.y -= _dt * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}

}
