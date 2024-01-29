#pragma once
#include "PlayableUnit.h"

#pragma region Declaration
class PlayerController;
#pragma endregion

class Warrior : public PlayableUnit
{
	using Super = PlayableUnit;
private:
	shared_ptr<GameObject>	_childCamera;
	shared_ptr<PlayerController> _controller;
public:
	Warrior();
	virtual ~Warrior();
protected:
	virtual void CharacterInit() override;
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

