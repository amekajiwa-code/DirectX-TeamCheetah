#pragma once
#include "ItemData.h"

class AncientRShoulderData : public ItemData
{
public:
	AncientRShoulderData();
	virtual ~AncientRShoulderData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

