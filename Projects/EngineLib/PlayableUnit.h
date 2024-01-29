#pragma once
#include "Unit.h"

class PlayableUnit : public Unit
{
	using Super = Unit;
public:
	PlayableUnit() {};
	virtual ~PlayableUnit() {};
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

