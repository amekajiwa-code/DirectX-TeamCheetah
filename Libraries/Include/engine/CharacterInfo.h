#pragma once
class CharacterInfo : public MonoBehaviour
{
public:
	CharacterInfo() {};
	virtual ~CharacterInfo() {};
public:
	void Reset();
public:
	CHARACTER_INFO GetCharacterInfo() { return _info; }
	void SetCharacterInfo(CHARACTER_INFO info)
	{
		_info = info;
	}
	const CHARACTER_ADD_INFO& GetAddCharacterInfo() const { return _addInfo; }
	void SetAddCharacterInfo(const CHARACTER_ADD_INFO& info) { _addInfo = info; }
private:
	CHARACTER_INFO _info;
	CHARACTER_ADD_INFO _addInfo;
};