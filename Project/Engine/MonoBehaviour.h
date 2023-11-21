#pragma once
#include "Component.h"

class MonoBehaviour : public Component
{
	using Super = Component;
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();
public:
	virtual void Awake() override;
	virtual void Update() override;
};

