#pragma once
#include "engine/IExecute.h"

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	//Shader
	shared_ptr<Shader>		_shader;
	//Camera
	shared_ptr<GameObject>	_camera;
};

