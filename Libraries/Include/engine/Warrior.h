#pragma once
#include "PlayableCharacter.h"

#pragma region Declaration
class PlayableCharacter;
class PlayerController;
#pragma endregion

class Warrior : public PlayableCharacter
{
	using Super = PlayableCharacter;
private:
	shared_ptr<GameObject>	_childCamera;
	shared_ptr<GameObject>	_childModel;
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

