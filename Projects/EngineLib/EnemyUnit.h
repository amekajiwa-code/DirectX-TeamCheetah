#pragma once
#include "Unit.h"

class EnemyUnit : public Unit
{
	using Super = Unit;
public:
	EnemyUnit() {};
	virtual ~EnemyUnit() {};
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

