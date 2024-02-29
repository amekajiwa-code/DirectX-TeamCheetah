#include "pch.h"
#include "AncientSword.h"
#include "ItemData.h"
#include "AncientSwordData.h"
#include "CharacterInfo.h"
#include <memory>

AncientSword::AncientSword()
{
}

AncientSword::~AncientSword()
{
}

void AncientSword::Init()
{
	shared_ptr<AncientSwordData> itemData = make_shared<AncientSwordData>();
	_itemData = itemData;
	_itemData->SetOwnerUnitInfo(_itemOwnerInfo);

	const auto& shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
	_itemModel = make_shared<ModelRenderer>(shader);
	_itemModel->SetModel(_itemData->GetItemMesh());
	_itemModel->SetPass(1);
	AddComponent(_itemModel);

	GetOrAddTransform();

	MANAGER_SCENE()->GetCurrentScene()->Add(shared_from_this());
}

bool AncientSword::ApplyItem(const bool& apply)
{
	if (_itemData == nullptr)
	{
		return false;
	}
	else
	{
		_itemData->ItemEffectToSelf(apply);
	}

	return true;
}

void AncientSword::Awake()
{
	Super::Awake();
}

void AncientSword::Start()
{
	Super::Start();
}

void AncientSword::FixedUpdate()
{
	Super::FixedUpdate();
	if (_itemOwnerAnimator != nullptr)
	{
		int animIndex = _itemOwnerAnimator->GetTweenDesc()->current.animIndex;
		int cuFrame = _itemOwnerAnimator->GetTweenDesc()->current.currentFrame;

		Matrix tf = _itemOwnerAnimator->GetAnimTransform()[animIndex].transforms[cuFrame][92];

		GetTransform()->isWroldMode = true;
		GetTransform()->SetLocalMatrix(tf);
		//Vec3 sc, rr, ts;
		//Quaternion rot;
		//tf.Decompose(sc, rot, ts);
		//rr = GetTransform()->QuatToEulerAngles(rot);
		//rr.x *= -1;
		//rr.z *= -1;
		//GetTransform()->SetLocalPosition(ts);
		//GetTransform()->SetLocalRotation(rr);
	}

}

void AncientSword::Update()
{

	Super::Update();
}

void AncientSword::LateUpdate()
{


	Super::LateUpdate();

}
