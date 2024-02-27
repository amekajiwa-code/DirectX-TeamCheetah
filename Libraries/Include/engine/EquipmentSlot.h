#pragma once
#include "MonoBehaviour.h"
#include "EquipmentItem.h"

#define MAX_EQUIPMENT_ITEM_SLOT (size_t)6

class EquipmentSlot : public MonoBehaviour
{
public:
	EquipmentSlot();
	virtual ~EquipmentSlot();
private:
	array<shared_ptr<EquipmentItem>, MAX_EQUIPMENT_ITEM_SLOT> _equipmentSlot;
public:

};

