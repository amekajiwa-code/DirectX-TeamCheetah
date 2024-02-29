#pragma once
#include "ItemData.h"

class AncientSwordData : public ItemData
{
public:
	AncientSwordData();
	virtual ~AncientSwordData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

