#include "pch.h"
#include "MagniBronzebeard.h"
#include "SphereCollider.h"
#include "HeightGetter.h"

MagniBronzebeard::MagniBronzebeard()
{

}

MagniBronzebeard::~MagniBronzebeard()
{

}

void MagniBronzebeard::CharacterInit()
{
	_childModel = make_shared<GameObject>();

	//Character
	{
		shared_ptr<Model> model = make_shared<Model>();
		{
			AddModelAndMaterial(model, L"MagniBronzebeard");
			AddAnimation(model, L"MagniBronzebeard", L"Stand");
		}
		const auto& shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		shared_ptr<ModelAnimator> tempAnimator = make_shared<ModelAnimator>(shader);
		{
			tempAnimator->SetModel(model);
			tempAnimator->SetPlay(true);
			tempAnimator->SetLoop(true);
			tempAnimator->SetPass(2);
		}
		_childModel->AddComponent(tempAnimator);
		_childModel->Awake();
		_childModel->Start();
		_childModel->SetName(L"Model");

		Vec3 rot = _childModel->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		_childModel->GetTransform()->SetLocalRotation(rot);
		_childModel->GetTransform()->SetLocalPosition(Vec3(0, 0, 0));
	}
	AddComponent(make_shared<SphereCollider>());
	SetName(L"MagniBronzebeard");
	AddChild(_childModel);
	GetTransform()->SetScale(Vec3(0.1f));

	{
		auto height = make_shared<HeightGetter>();
		height->Set(MANAGER_SCENE()->GetCurrentScene()->GetCurrentTerrain().get());
		AddComponent(height);
	}
}

void MagniBronzebeard::Awake()
{
	Super::Awake();
	CharacterInit();
}

void MagniBronzebeard::Start()
{
	Super::Start();
}

void MagniBronzebeard::FixedUpdate()
{
	Super::FixedUpdate();
}

void MagniBronzebeard::Update()
{
	Super::Update();
}

void MagniBronzebeard::LateUpdate()
{
	Super::LateUpdate();
}
