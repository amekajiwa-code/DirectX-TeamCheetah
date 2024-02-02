#include "pch.h"
#include "CoreHound.h"

CoreHound::CoreHound()
{
}

CoreHound::~CoreHound()
{
}

void CoreHound::CharacterInit()
{
	_childModel = make_shared<GameObject>();


	//Character
	{
		shared_ptr<Model> model = make_shared<Model>();
		{
			AddModelAndMaterial(model, L"CoreHound");
			AddAnimation(model, L"CoreHound", L"Stand");
			AddAnimation(model, L"CoreHound", L"Walk");
			AddAnimation(model, L"CoreHound", L"Run");
			AddAnimation(model, L"CoreHound", L"Damaged");
			AddAnimation(model, L"CoreHound", L"Death");
			AddAnimation(model, L"CoreHound", L"Battle");
			AddAnimation(model, L"CoreHound", L"Attack1");
			AddAnimation(model, L"CoreHound", L"Attack2");
		}
		const auto& shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		shared_ptr<ModelAnimator> tempAnimator = make_shared<ModelAnimator>(shader);
		{
			tempAnimator->SetModel(model);
			tempAnimator->SetPlay(true);
			tempAnimator->SetLoop(true);
			tempAnimator->SetPass(1);
		}
		_childModel->AddComponent(tempAnimator);
		_childModel->Awake();
		_childModel->Start();
		_childModel->SetName(L"Model");
		tempAnimator->GetTweenDesc().ClearNextAnim();
		tempAnimator->SetNextAnimation(L"Death");

		Vec3 rot = _childModel->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		_childModel->GetTransform()->SetLocalRotation(rot);
		_childModel->GetTransform()->SetLocalPosition(Vec3(0,150,0));
	}
	SetName(L"CoreHound");
	AddChild(_childModel);
	GetTransform()->SetScale(Vec3(0.1f));
}

void CoreHound::Awake()
{
	Super::Awake();
	CharacterInit();
}

void CoreHound::Start()
{
	Super::Start();
}

void CoreHound::FixedUpdate()
{
	Super::FixedUpdate();
}

void CoreHound::Update()
{
	Super::Update();
}

void CoreHound::LateUpdate()
{
	Super::LateUpdate();
}
