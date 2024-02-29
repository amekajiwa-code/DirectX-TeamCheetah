#pragma once
#include "ItemData.h"

class AncientBeltData : public ItemData
{
public:
	AncientBeltData();
	virtual ~AncientBeltData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

