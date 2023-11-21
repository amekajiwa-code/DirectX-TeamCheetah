#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(Component(ComponentType::Camera))
{
}

Camera::~Camera()
{
}

void Camera::UpdateMatrix()
{
	Vec3 eye = GetTransform()->GetPosition();
	Vec3 look = eye + GetTransform()->GetLookVector();
	Vec3 up = GetTransform()->GetUpVector();
	S_MatView = ::XMMatrixLookAtLH(eye, look, up);

	//S_MatView = GetTransform()->GetWorldMatrix().Invert();

	switch (_type)
	{
	case ProjectionType::Perspective:
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)g_winSizeX / (float)g_winSizeY, 1.f, 100.f);
	}break;
	case ProjectionType::Orthographic:
	{
		S_MatProjection = ::XMMatrixOrthographicLH(g_winSizeX, g_winSizeY, 0.f, 1.f);
	}break;
	}
}

void Camera::Update()
{
	UpdateMatrix();
}
