#pragma once
#include "engine/IExecute.h"

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<Shader> _shader;
	//obj
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;
	//Camera
	shared_ptr<GameObject> _camera;
};

