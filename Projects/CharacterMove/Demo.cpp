#include "pch.h"
#include "Demo.h"


void Demo::Init(){

	shared_ptr<BaseScene> scene = make_shared<BaseScene>();
	MANAGER_SCENE()->ChangeScene(scene);
}

void Demo::Update()
{
}

void Demo::Render()
{
}
