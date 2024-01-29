#pragma once
#include "EnemyUnit.h"
class CoreHound : public EnemyUnit
{
	using Super = EnemyUnit;
public:
	CoreHound();
	virtual ~CoreHound();
protected:
	virtual void CharacterInit() override;
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

