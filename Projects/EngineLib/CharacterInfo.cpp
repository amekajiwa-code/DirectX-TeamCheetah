#include "pch.h"
#include "CharacterInfo.h"

void CharacterInfo::Reset()
{
	_info._hp = _info._maxHp;
	_info._mp = _info._maxMp;
}
