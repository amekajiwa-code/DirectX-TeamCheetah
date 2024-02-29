#pragma once
#include "ItemData.h"

class AncientLShoulderData : public ItemData
{
public:
	AncientLShoulderData();
	virtual ~AncientLShoulderData();
public:
	virtual bool ItemEffectToSelf(bool active) override;
};

