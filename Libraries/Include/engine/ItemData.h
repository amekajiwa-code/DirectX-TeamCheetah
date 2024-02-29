#pragma once
#include "MonoBehaviour.h"

class CharacterInfo;

class ItemData : public MonoBehaviour
{
public:
	ItemData();
	virtual ~ItemData();
protected:
	wstring					_itemLoadPath;
	wstring					_itemSavePath;
	weak_ptr<CharacterInfo> _itemOwnerUnitInfo;
	ItemInfo				_itemInfo;
	shared_ptr<Model>		_itemMesh;
	shared_ptr<Texture>		_itemImage;
	bool					_isApply = false;
public:
	bool LoadItemInformationFromFile(const wstring& loadPath);
	bool SaveItemInformationToFile(const wstring& savePath);
public:
	void SetItemInfo(const ItemInfo& info) { _itemInfo = info; }
	void SetItemMesh(const shared_ptr<Model>& mesh) { _itemMesh = mesh; }
	void SetItemImage(const shared_ptr<Texture>& image) { _itemImage = image; }
	void SetOwnerUnitInfo(const shared_ptr<CharacterInfo>& info) { _itemOwnerUnitInfo = info; }
public:
	const ItemInfo& GetItemInfo() const { return _itemInfo; }
	const shared_ptr<Model>& GetItemMesh() const { return _itemMesh; }
	const shared_ptr<Texture>& GetItemImage() const { return _itemImage; }
public:
	virtual bool ItemEffectToSelf(bool active);
	virtual bool ItemEffectToTarget(const shared_ptr<GameObject>& target);
};

