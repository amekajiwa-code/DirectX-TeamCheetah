#pragma once
#include "Unit.h"

class PlayableCharacter : public Unit
{
	using Super = GameObject;
public:
	PlayableCharacter() {};
	virtual ~PlayableCharacter() {};
protected:
	virtual void CharacterInit() {};
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

