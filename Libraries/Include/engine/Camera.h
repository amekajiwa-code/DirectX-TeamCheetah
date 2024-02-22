#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();
//member
private:
	ProjectionType _type = ProjectionType::Perspective;
	CameraType _camType = CameraType::Normal;
private:
	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;
	Matrix _matAround = Matrix::Identity;

	float _near = 0.1f;
	float _far = 10000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;
private:
	Vec3 _target;
private:
	Vec3 _eye;
	Vec3 _look;
	Vec3 _up;
public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
//function
public:
	void SetProjectionType(ProjectionType type) { _type = type; }
	void SetNear(float value) { _near = value; }
	void SetPar(float value) { _far = value; }
	void SetFov(float value) { _fov = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }
	void SetCameraType(CameraType type) { _camType = type; }
public:
	ProjectionType GetProjectionType() const { return _type; }
	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }
public:
	void UpdateMatrix();
public:
	virtual void Update() override;
};

