#pragma once

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	~PlayerController();
private:
	weak_ptr<Transform> _transform;
	Vec3 _look;
	Vec3 _right;
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _pos;
	Vec3 _target;
private:
	weak_ptr<ModelAnimator> _animator;
	float _speed = 200.f;
	float _dt = 0.f;
private:
	weak_ptr<GameObject> _camera;
	Vec3 _prevMousePos;
	Vec3 _currentMousePos;
	Vec3 _camRotation;
private:
	void CameraMove();
	void PlayerInput();
public:
	void ReceiveEvent(const EventArgs& args);
	void DispatchEvent();
public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

