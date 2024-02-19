#pragma once
#include "Component.h"

class BaseCollider : public Component
{
public:
	BaseCollider(ColliderType colliderType);
	virtual ~BaseCollider();
protected:
	ColliderType _colliderType;
public:
	const ColliderType& GetColliderType() const { return _colliderType; }
public:
	virtual bool Intersects(const Ray& ray, OUT float& distance) = 0;
};

