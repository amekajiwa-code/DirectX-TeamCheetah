#pragma once

class ItemData;
class CharacterInfo;

class Item : public GameObject
{
	using Super = GameObject;
public:
	Item(){}
	virtual ~Item(){}
protected:
	shared_ptr<ModelRenderer>	_itemModel;
	shared_ptr<ModelAnimator>	_itemOwnerAnimator;
	shared_ptr<ItemData>		_itemData;
	shared_ptr<CharacterInfo>   _itemOwnerInfo;
public:
	void SetItemOwnerInfo(const shared_ptr<CharacterInfo>& info) { _itemOwnerInfo = info; }
	void SetItemOwnerAnimator(const shared_ptr<ModelAnimator>& Animator) { _itemOwnerAnimator = Animator; }
public:
	virtual void Init() {}
	virtual bool ApplyItem(const bool& apply) { return false; }
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

