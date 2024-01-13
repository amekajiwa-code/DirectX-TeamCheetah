#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(Component(ComponentType::Camera))
{
	_width = static_cast<float>(g_gameDesc.width);
	_height = static_cast<float>(g_gameDesc.height);
}

Camera::~Camera()
{
}

Matrix Camera::CalculateViewMat(const Vec3 axis)
{
	Matrix fMat;

	fMat = ::XMMatrixLookAtLH(_eye, _look, _up);

	Matrix rotmat = Matrix::CreateRotationX(axis.x);

	fMat = ::XMMatrixMultiply(rotmat, fMat);

	return fMat;
}

void Camera::UpdateMatrix()
{
	switch (_camType)
	{
	case CameraType::Debug:
	case CameraType::Normal: 
	{
		_eye = GetTransform()->GetPosition();
		_look = _eye + GetTransform()->GetLookVector();
		_up = GetTransform()->GetUpVector();

	}break;
	case CameraType::Target:
	{
		_eye = GetTransform()->GetPosition();
		_look = GetGameObject()->GetParent()->GetTransform()->GetPosition();
		_look.y += 10.f;
		_up = GetTransform()->GetUpVector();
	}break;
	}

	S_MatView = _matView = ::XMMatrixLookAtLH(_eye, _look, _up);

	switch (_type)
	{
	case ProjectionType::Perspective:
	{
		S_MatProjection = _matProjection = ::XMMatrixPerspectiveFovLH(_fov, (_width / _height), _near, _far);
	}break;
	case ProjectionType::Orthographic:
	{
		S_MatProjection = _matProjection = ::XMMatrixOrthographicLH(_width, _height, _near, _far);
	}break;
	}
}

void Camera::Update()
{
	UpdateMatrix();
}
