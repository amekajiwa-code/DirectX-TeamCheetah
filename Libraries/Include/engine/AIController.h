#pragma once

#pragma region Declaration
class EnemyAnimState;
class EnemyAnimStand;
class EnemyAnimWalk;
class EnemyAnimRun;
class EnemyAnimDamaged;
class EnemyAnimDeath;
class EnemyAnimBattle;
class EnemyAnimAttack1;
class EnemyAnimAttack2;
class EnemyAnimCasting;
class EnemyAnimAbility1;
class EnemyAnimAbility2;
#pragma endregion

class AIController : public MonoBehaviour, public enable_shared_from_this<AIController>
{
public:
	AIController(){}
	virtual ~AIController(){}
private:
	weak_ptr<Transform>			_transform;
	Vec3						_targetPos;
	shared_ptr<EnemyUnitState>	_currentState;
	bool _isBattle = false;
	bool _isDamaged = false;
private:
	weak_ptr<ModelAnimator>				_animator;
	shared_ptr<EnemyAnimState>			_currentAnimState;
	vector<shared_ptr<EnemyAnimState>>	_animStateList;
private:
	void InitAnimState();
public:
	bool SetAnimState(const EnemyAnimType& type);
public:
	const shared_ptr<ModelAnimator>& GetAnimator() { return _animator.lock(); }
	const shared_ptr<EnemyUnitState>& GetCurrentUnitState() { return _currentState; }
public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

