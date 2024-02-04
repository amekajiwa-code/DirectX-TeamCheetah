#include "pch.h"
#include "LavaFlow.h"

void Lava::Update()
{
	float time= MANAGER_TIME()->GetDeltaTime();
	
	reverse ? currentDistance -= (speed * time) : currentDistance += (speed * time);

	if (currentDistance > maxDistance) {
		reverse = true;
	}
	if (currentDistance < 0) {
		reverse = false;
	}
	auto posi = GetTransform()->GetLocalPosition();
	posi.x = currentDistance;
	posi.z = currentDistance;
	if (enableHeight) {
		posi.y = currentDistance/10;
	}
	GetTransform()->SetLocalPosition(posi);
}
