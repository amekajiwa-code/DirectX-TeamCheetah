#pragma once
#include "Unit.h"

class NpcUnit : public Unit
{
	using Super = Unit;
public:
	NpcUnit() {};
	virtual ~NpcUnit() {};
private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

