#pragma once
#include "Item.h"

class AncientSword : public Item
{
	using Super = Item;
private:
	vector<AnimTransform>* _animTransforms;
public:
	AncientSword();
	virtual ~AncientSword();
public:
	virtual void Init() override;
	virtual bool ApplyItem(const bool& apply) override;
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

