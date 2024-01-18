#pragma once

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	~PlayerController();
private:
	weak_ptr<Transform> _transform;
	Vec3 _movePos;
	Vec3 _moveForward;
	Vec3 _moveRight;
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _target;
	float _camSpeed = 2000.f;
	Vec3 _jumpStartPos;
	Vec3 _jumpUpMaxPos;
	Vec3 _jumpUpDir = { 0,1,0 };
	Vec3 _jumpDownDir = { 0,-1,0 };
	float _jumpPower = 18.f;
	bool _isJumpUP = false;
	bool _isJumpFall = false;
	bool _isJump = false;
private:
	weak_ptr<ModelAnimator> _animator;
	PlayerAnimState _currentAnimState = PlayerAnimState::Idle;
	PlayerAnimState _prevAnimState = PlayerAnimState::Idle;
	float _speed = 300.f;
	float _dt = 0.f;
	float _camDist = 0.f;
private:
	weak_ptr<GameObject> _camera;
	Vec3 _prevMousePos;
	Vec3 _currentMousePos;
	Vec3 _camRot;
	Vec3 _camPos;
	Vec3 _rCamPos;
	Vec3 _playerRot;
	Vec3 _playerPos;
private:
	//Camera
	void CameraMove();
	//Player
	void PlayerInput();
	void PlayerMove();
	void PlayerJump();
	void PlayerAnimControll();
public:
	void ReceiveEvent(const EventArgs& args);
	void DispatchEvent();
public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

