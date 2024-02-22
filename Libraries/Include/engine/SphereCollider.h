#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
	using Super = BaseCollider;
public:
	SphereCollider();
	virtual ~SphereCollider();
private:
	float			_radius = 180;
	BoundingSphere	_boundingSphere;
	Vec3			_sphereWeight = Vec3(0.f);
public:
	void SetRadius(float radius) { _radius = radius; }
public:
	BoundingSphere& GetBoundingSphere() { return _boundingSphere; }
public:
	virtual bool Intersects(const Ray& ray, OUT float& distance) override;
	virtual void Update() override;
};

