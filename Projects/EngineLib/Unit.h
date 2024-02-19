#pragma once
#include "GameObject.h"

class BaseCollider;
class BoxCollider;
class SphereCollider;

class Unit : public GameObject
{
	using Super = GameObject;
public:
	Unit() {};
	virtual ~Unit() {};
protected:
	shared_ptr<GameObject>	_childModel;
	shared_ptr<BoxCollider> _collider;
protected:
	virtual void CharacterInit() {};
	void AddAnimation(const shared_ptr<Model>& com, wstring animOwner, wstring animName);
	void AddModelAndMaterial(const shared_ptr<Model>& com, wstring name);
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

