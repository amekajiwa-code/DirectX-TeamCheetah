#pragma once
#include "CharacterController.h"
#include "AnimState.h"

class AIController : public CharacterController, public enable_shared_from_this<AIController>
{
public:
	AIController(){}
	virtual ~AIController(){}
private:
	weak_ptr<Transform>			_transform;
	weak_ptr<ModelAnimator>		_animator;
	shared_ptr<JumpFlag>		_jumpState;
	Vec3						_targetPos;
	AIType						_type = AIType::None;
	float _defaultSpeed = 300.f;
	float _currentSpeed = 300.f;
	float _slowSpeed = 150.f;
	bool _isBattle = false;
	bool _isDamaged = false;
	bool _isSlow = false;
private:
	//Player
	shared_ptr<PlayerUnitState> _currentPlayerState;
	shared_ptr<PlayerAnimState> _currentPlayerAnimState;
	vector<shared_ptr<PlayerAnimState>> _playerAnimStateList;
private:
	//Enemy
	shared_ptr<EnemyUnitState>	_currentEnemyState;
	shared_ptr<EnemyAnimState>	_currentEnemyAnimState;
	vector<shared_ptr<EnemyAnimState>>	_enemyAnimStateList;
private:
	void InitAnimState();
public:
	bool SetAnimState(const PlayerAnimType& type);
	bool SetAnimState(const EnemyAnimType& type);
	void SetAIType(AIType type) { _type = type; }
public:
	const shared_ptr<ModelAnimator>& GetAnimator() { return _animator.lock(); }
	const float& GetDefaultSpeed() const { return _defaultSpeed; }
	const float& GetCurrentSpeed() const { return _currentSpeed; }
	const shared_ptr<JumpFlag>& GetJumpState() { return _jumpState; }
public:
	const shared_ptr<PlayerUnitState>& GetCurrentPlayerUnitState() { return _currentPlayerState; }
	const shared_ptr<EnemyUnitState>& GetCurrentEnemyUnitState() { return _currentEnemyState; }
	const PlayerAnimType& GetCurrentPlayerAnimType() { return _currentPlayerAnimState->GetStateAnimtype(); }
	const EnemyAnimType& GetCurrentEnemyAnimType() { return _currentEnemyAnimState->GetStateAnimtype(); }
public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

