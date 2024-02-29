#pragma once
#include "ItemData.h"

class AncientHelmData : public ItemData
{
public:
	AncientHelmData();
	virtual ~AncientHelmData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

