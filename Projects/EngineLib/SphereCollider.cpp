#include "pch.h"
#include "SphereCollider.h"
#include "DebugDraw.h"

SphereCollider::SphereCollider() : Super(ColliderType::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

bool SphereCollider::Intersects(const Ray& ray, OUT float& distance)
{
	return _boundingSphere.Intersects(ray.position, ray.direction, OUT distance);
}

void SphereCollider::Update()
{
	_boundingSphere.Center = GetGameObject()->GetTransform()->GetPosition();
	_sphereWeight = GetGameObject()->GetTransform()->GetScale();
	_boundingSphere.Radius = _radius * max(max(_sphereWeight.x, _sphereWeight.y), _sphereWeight.z);
}
