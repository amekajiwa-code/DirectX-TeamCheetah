#pragma once

class CameraMove : public MonoBehaviour
{
public:
	float _dt = 0.f;
	float _speed = 10.f;
public:
	virtual void Start() override;
	virtual void Update() override;
};

