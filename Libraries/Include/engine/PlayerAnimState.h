#pragma once

#pragma region Declaration
class CharacterController;
class PlayerController;
class AIController;
struct JumpFlag;
#pragma endregion

#pragma region PlayerAnimationStateMachine
class PlayerAnimState
{
protected:
	weak_ptr<PlayerController>		_contoller;
	weak_ptr<AIController>			_aiContoller;
	weak_ptr<ModelAnimator>			_animator;
	weak_ptr<PlayerUnitState>		_playerState;
	PlayerAnimType					_stateAnim = PlayerAnimType::None;
public:
	PlayerAnimState() {};
	virtual ~PlayerAnimState() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) = 0;
	virtual bool Update() = 0;
	virtual bool Out() = 0;
	PlayerAnimType& GetStateAnimtype() { return _stateAnim; }
};

class PlayerAnimIdle : public PlayerAnimState
{
public:
	PlayerAnimIdle() {};
	virtual ~PlayerAnimIdle() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimFrontWalk : public PlayerAnimState
{
public:
	PlayerAnimFrontWalk() {};
	virtual ~PlayerAnimFrontWalk() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimBackWalk : public PlayerAnimState
{
public:
	PlayerAnimBackWalk() {};
	virtual ~PlayerAnimBackWalk() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimFrontRun : public PlayerAnimState
{
public:
	PlayerAnimFrontRun() {};
	virtual ~PlayerAnimFrontRun() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimBackRun : public PlayerAnimState
{
public:
	PlayerAnimBackRun() {};
	virtual ~PlayerAnimBackRun() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpStart : public PlayerAnimState
{
private:
	weak_ptr<JumpFlag> _jumpState;
public:
	PlayerAnimJumpStart() {};
	virtual ~PlayerAnimJumpStart() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpFall : public PlayerAnimState
{
private:
	weak_ptr<JumpFlag> _jumpState;
public:
	PlayerAnimJumpFall() {};
	virtual ~PlayerAnimJumpFall() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimJumpEnd : public PlayerAnimState
{
private:
	weak_ptr<JumpFlag> _jumpState;
public:
	PlayerAnimJumpEnd() {};
	virtual ~PlayerAnimJumpEnd() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimStun : public PlayerAnimState
{
public:
	PlayerAnimStun() {};
	virtual ~PlayerAnimStun() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimLoot : public PlayerAnimState
{
public:
	PlayerAnimLoot() {};
	virtual ~PlayerAnimLoot() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimDamaged : public PlayerAnimState
{
public:
	PlayerAnimDamaged() {};
	virtual ~PlayerAnimDamaged() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimDeath : public PlayerAnimState
{
public:
	PlayerAnimDeath() {};
	virtual ~PlayerAnimDeath() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimBattle : public PlayerAnimState
{
public:
	PlayerAnimBattle() {};
	virtual ~PlayerAnimBattle() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimAttack1 : public PlayerAnimState
{
public:
	PlayerAnimAttack1() {};
	virtual ~PlayerAnimAttack1() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimAttack2 : public PlayerAnimState
{
public:
	PlayerAnimAttack2() {};
	virtual ~PlayerAnimAttack2() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimCasting : public PlayerAnimState
{
public:
	PlayerAnimCasting() {};
	virtual ~PlayerAnimCasting() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimAbility1 : public PlayerAnimState
{
public:
	PlayerAnimAbility1() {};
	virtual ~PlayerAnimAbility1() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};

class PlayerAnimAbility2 : public PlayerAnimState
{
public:
	PlayerAnimAbility2() {};
	virtual ~PlayerAnimAbility2() {};
public:
	virtual bool Enter(const shared_ptr<CharacterController>& playerController) override;
	virtual bool Update() override;
	virtual bool Out() override;
};
#pragma endregion

