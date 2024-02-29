#pragma once
#include "ItemData.h"

class AncientShieldData : public ItemData
{
public:
	AncientShieldData();
	virtual ~AncientShieldData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

