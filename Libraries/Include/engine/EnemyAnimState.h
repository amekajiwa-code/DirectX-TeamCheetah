#pragma once

#pragma region Declaration
class CharacterController;
class AIController;
#pragma endregion

#pragma region EnemyAnimationStateMachine
class EnemyAnimState
{
public:
	EnemyAnimState() {}
	virtual ~EnemyAnimState() {}
protected:
	weak_ptr<AIController>		_controller;
	weak_ptr<ModelAnimator>		_animator;
	weak_ptr<EnemyUnitState>	_state;
	EnemyAnimType				_animType;
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) { return false; }
	virtual bool Update() { return false; }
	virtual bool Out() { return false; }
	EnemyAnimType GetStateAnimtype() { return _animType; }

};

class EnemyAnimStand : public EnemyAnimState
{
public:
	EnemyAnimStand() {}
	virtual ~EnemyAnimStand() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimWalk : public EnemyAnimState
{
public:
	EnemyAnimWalk() {}
	virtual ~EnemyAnimWalk() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimRun : public EnemyAnimState
{
public:
	EnemyAnimRun() {}
	virtual ~EnemyAnimRun() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimDamaged : public EnemyAnimState
{
public:
	EnemyAnimDamaged() {}
	virtual ~EnemyAnimDamaged() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimDeath : public EnemyAnimState
{
public:
	EnemyAnimDeath() {}
	virtual ~EnemyAnimDeath() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimBattle : public EnemyAnimState
{
public:
	EnemyAnimBattle() {}
	virtual ~EnemyAnimBattle() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimAttack1 : public EnemyAnimState
{
public:
	EnemyAnimAttack1() {}
	virtual ~EnemyAnimAttack1() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimAttack2 : public EnemyAnimState
{
public:
	EnemyAnimAttack2() {}
	virtual ~EnemyAnimAttack2() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimCasting : public EnemyAnimState
{
public:
	EnemyAnimCasting() {}
	virtual ~EnemyAnimCasting() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimAbility1 : public EnemyAnimState
{
public:
	EnemyAnimAbility1() {}
	virtual ~EnemyAnimAbility1() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class EnemyAnimAbility2 : public EnemyAnimState
{
public:
	EnemyAnimAbility2() {}
	virtual ~EnemyAnimAbility2() {}
public:
	virtual bool Enter(const shared_ptr<CharacterController>& enemyController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};
#pragma endregion
