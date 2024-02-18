#pragma once
#include "CharacterController.h"

#pragma region Declaration
class PlayerAnimState;
class PlayerAnimIdle;
class PlayerAnimRun;
class PlayerAnimBackRun;
class PlayerAnimJumpStart;
class PlayerAnimJumpFall;
class PlayerAnimJumpEnd;
#pragma endregion



class PlayerController : public CharacterController, public enable_shared_from_this<PlayerController>
{
public:
	PlayerController();
	~PlayerController();
private:
	weak_ptr<Transform> _transform;
	Vec3 _movePos = { 0,0,0 };
	Vec3 _moveForward = { 0,0,0 };
	Vec3 _moveRight = { 0,0,0 };
	Vec3 _scale = { 1,1,1 };
	Vec3 _rotation = { 0,0,0 };
	Vec3 _target = { 0,0,0 };
	Vec3 _jumpStartPos = { 0,0,0 };
	Vec3 _jumpUpMaxPos = { 0,0,0 };
	Vec3 _jumpUpDir = { 0,1,0 };
	Vec3 _jumpDownDir = { 0,-1,0 };
	float _jumpPower = 20.f;
	shared_ptr<JumpFlag>		_jumpState;
	shared_ptr<PlayerUnitState>	_currentState;
	bool _isAttack = false;
	bool _isMove = false;
	bool _isBattle = false;
	float _battleTime = 0.f;

	float _attackTimer = 0.0f;
	shared_ptr<Terrain> _terrain;
private:
	//Animation Controll
	weak_ptr<ModelAnimator>				_animator;
	shared_ptr<PlayerAnimState>			_animState;
	vector<shared_ptr<PlayerAnimState>> _animStateList;
	float _defaultSpeed = 300.f;
	float _currentSpeed = 300.f;
	float _slowSpeed = 150.f;
	float _dt = 0.f;
	bool _isSlow = false;
private:
	//Camera Controll
	weak_ptr<GameObject> _camera;
	Vec3 _prevMousePos;
	Vec3 _currentMousePos;
	Vec3 _camRot;
	Vec3 _camPos;
	Vec3 _rCamPos;
	Vec3 _playerRot;
	Vec3 _playerPos;
	float _camDist = 0.f;
	float _camSpeed = 2000.f;
private:
	void AnimStateInit();
	//Player
	void PlayerInput();
	void PlayerMove();
	void PlayerJump();
	void PlayerAttack();
	void KeyStateCheck();
	//Camera
	void CameraMove();
public:
	bool SetAnimState(const PlayerAnimType& animType);
	const shared_ptr<ModelAnimator>& GetAnimator() { return _animator.lock(); }
	const shared_ptr<PlayerUnitState>& GetCurrentUnitState() { return _currentState; }
	const PlayerAnimType& GetCurrentAnimType();
	const shared_ptr<JumpFlag>& GetJumpState() { return _jumpState; }
	const float& GetDefaultSpeed() const { return _defaultSpeed; }
	const float& GetCurrentSpeed() const { return _currentSpeed; }
	bool GetMoveState() const { return _isMove; }
	bool GetAttackState() const { return _isAttack; }
	bool GetBattleState() const { return _isBattle; }

public:
	void ReceiveEvent(const EventArgs& args);
	void DispatchEvent();
public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

