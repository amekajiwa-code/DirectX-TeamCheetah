#pragma once
#include "engine/IExecute.h"

class PlayableCharacter;
class Warrior;

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	//Shader
	shared_ptr<Shader>		_shader;
	//Character
	shared_ptr<PlayableCharacter> _warrior;
	//Map
	shared_ptr<GameObject>	_map;
};

