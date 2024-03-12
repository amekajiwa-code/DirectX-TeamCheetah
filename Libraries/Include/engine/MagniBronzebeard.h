#pragma once
#include "NpcUnit.h"
class MagniBronzebeard : public NpcUnit
{
	using Super = Unit;
public:
	MagniBronzebeard();
	virtual ~MagniBronzebeard() ;
protected:
	virtual void CharacterInit() override;
private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

