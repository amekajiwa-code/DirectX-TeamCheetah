#pragma once

class PlayerController;

class PlayerAnimState
{
protected:
	weak_ptr<PlayerController>	_contoller;
	weak_ptr<ModelAnimator>		_animator;
	PlayerUnitState				_state = PlayerUnitState::None;
	PlayerUnitState				_playerState = PlayerUnitState::None;
public:
	PlayerAnimState() {};
	virtual ~PlayerAnimState() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) = 0;
	virtual bool Update() = 0;
	virtual bool Out() = 0;
};

class PlayerAnimIdle : public PlayerAnimState
{
public:
	PlayerAnimIdle() {};
	virtual ~PlayerAnimIdle() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimFrontWalk : public PlayerAnimState
{
public:
	PlayerAnimFrontWalk() {};
	virtual ~PlayerAnimFrontWalk() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimBackWalk : public PlayerAnimState
{
public:
	PlayerAnimBackWalk() {};
	virtual ~PlayerAnimBackWalk() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimRun : public PlayerAnimState
{
public:
	PlayerAnimRun() {};
	virtual ~PlayerAnimRun() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimBackRun : public PlayerAnimState
{
public:
	PlayerAnimBackRun() {};
	virtual ~PlayerAnimBackRun() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpStart : public PlayerAnimState
{
public:
	PlayerAnimJumpStart() {};
	virtual ~PlayerAnimJumpStart() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpFall : public PlayerAnimState
{
public:
	PlayerAnimJumpFall() {};
	virtual ~PlayerAnimJumpFall() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpEnd : public PlayerAnimState
{
public:
	PlayerAnimJumpEnd() {};
	virtual ~PlayerAnimJumpEnd() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpEndRun : public PlayerAnimState
{
public:
	PlayerAnimJumpEndRun() {};
	virtual ~PlayerAnimJumpEndRun() {};
public:
	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};


//
//class PlayerAnimStun : public PlayerAnimState
//{
//public:
//	PlayerAnimStun() {};
//	virtual ~PlayerAnimStun() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimLoot : public PlayerAnimState
//{
//public:
//	PlayerAnimLoot() {};
//	virtual ~PlayerAnimLoot() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimDeath : public PlayerAnimState
//{
//public:
//	PlayerAnimDeath() {};
//	virtual ~PlayerAnimDeath() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimBattle : public PlayerAnimState
//{
//public:
//	PlayerAnimBattle() {};
//	virtual ~PlayerAnimBattle() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimAttack1 : public PlayerAnimState
//{
//public:
//	PlayerAnimAttack1() {};
//	virtual ~PlayerAnimAttack1() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimAttack2 : public PlayerAnimState
//{
//public:
//	PlayerAnimAttack2() {};
//	virtual ~PlayerAnimAttack2() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimCasting : public PlayerAnimState
//{
//public:
//	PlayerAnimCasting() {};
//	virtual ~PlayerAnimCasting() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimAbility1 : public PlayerAnimState
//{
//public:
//	PlayerAnimAbility1() {};
//	virtual ~PlayerAnimAbility1() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};
//
//class PlayerAnimAbility2 : public PlayerAnimState
//{
//public:
//	PlayerAnimAbility2() {};
//	virtual ~PlayerAnimAbility2() {};
//public:
//	virtual bool Enter(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Update(const shared_ptr<PlayerController>& playerController) override;
//	virtual bool Out(const shared_ptr<PlayerController>& playerController) override;
//};