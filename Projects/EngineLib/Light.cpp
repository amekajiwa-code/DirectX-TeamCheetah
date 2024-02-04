#include "pch.h"
#include "Light.h"

Light::Light() : Component(ComponentType::Light)
{

}

Light::~Light()
{

}

void Light::Update()
{
	//RENDER->PushLightData(_desc);
}
