#pragma once
class CharacterInfo : public MonoBehaviour
{
public:
	CharacterInfo() {};
	virtual ~CharacterInfo() {};

	CHARACTER_INFO GetCharacterInfo() { return _info; }
	void SetCharacterInfo(CHARACTER_INFO info)
	{
		_info = info;
	}
private:
	CHARACTER_INFO _info;
};