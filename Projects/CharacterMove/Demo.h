#pragma once
#include "engine/IExecute.h"

class Unit;


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
	shared_ptr<Unit> _warrior;
	shared_ptr<Unit> _coreHound;
	//Map
	shared_ptr<GameObject>	_map;
};

