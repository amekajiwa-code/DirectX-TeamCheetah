#include "pch.h"
#include "AncientRShoulderData.h"
#include "CharacterInfo.h"

AncientRShoulderData::AncientRShoulderData()
{
	_itemLoadPath = DATA_ADDR_ITEM;
	_itemLoadPath += L"Equipment/RightShoulder/Warrior/AncientRShoulderData.xml";

	_itemSavePath = _itemLoadPath;
	LoadItemInformationFromFile(_itemLoadPath);
}

AncientRShoulderData::~AncientRShoulderData()
{
}

bool AncientRShoulderData::ItemEffectToSelf(bool active)
{
	if (_itemOwnerUnitInfo.lock() == nullptr ||
		_itemInfo.Name == L"")
	{
		return false;
	}
	else
	{
		if (active)
		{
			if (_isApply == false)
			{
				auto tempinfo = _itemOwnerUnitInfo.lock()->GetAddCharacterInfo();
				tempinfo._AddHP += _itemInfo.HP;
				tempinfo._AddMP += _itemInfo.MP;
				tempinfo._AddATK += _itemInfo.ATK;
				tempinfo._AddDEF += _itemInfo.DEF;
			}
		}
		else
		{
			if (_isApply == true)
			{
				auto tempinfo = _itemOwnerUnitInfo.lock()->GetAddCharacterInfo();
				tempinfo._AddHP -= _itemInfo.HP;
				tempinfo._AddMP -= _itemInfo.MP;
				tempinfo._AddATK -= _itemInfo.ATK;
				tempinfo._AddDEF -= _itemInfo.DEF;
			}
		}
	}

	return true;
}
