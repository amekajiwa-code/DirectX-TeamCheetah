#include "pch.h"
#include "Warrior.h"
#include "PlayerController.h"
#include "HeightGetter.h"

Warrior::Warrior()
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();
	_objType = ObjectType::PlayableUnit;
}

Warrior::~Warrior()
{
}

void Warrior::CharacterInit()
{
	_childModel = make_shared<GameObject>();

	//Character
	{
		shared_ptr<Model> model = make_shared<Model>();
		{
			AddModelAndMaterial(model, L"Warrior");
			AddAnimation(model, L"Warrior", L"Stand");
			AddAnimation(model, L"Warrior", L"FrontWalk");
			AddAnimation(model, L"Warrior", L"BackWalk");
			AddAnimation(model, L"Warrior", L"FrontRun");
			AddAnimation(model, L"Warrior", L"BackRun");
			AddAnimation(model, L"Warrior", L"JumpStart");
			AddAnimation(model, L"Warrior", L"JumpFall");
			AddAnimation(model, L"Warrior", L"JumpEnd");
			AddAnimation(model, L"Warrior", L"Battle");
			AddAnimation(model, L"Warrior", L"Attack1");
			AddAnimation(model, L"Warrior", L"Attack2");
			AddAnimation(model, L"Warrior", L"Ability1");
			AddAnimation(model, L"Warrior", L"Ability2");
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
	}
	{
		auto height = make_shared<HeightGetter>();
		height->Set(MANAGER_SCENE()->GetCurrentScene()->GetCurrentTerrain().get());
		AddComponent(height);
	}
	SetName(L"Warrior");
	AddChild(_childModel);
	GetTransform()->SetScale(Vec3(0.1f));
}

void Warrior::Awake()
{
	Super::Awake();

	CharacterInit();
}

void Warrior::Start()
{
	Super::Start();
}

void Warrior::FixedUpdate()
{
	Super::FixedUpdate();
}

void Warrior::Update()
{
	Super::Update();
}

void Warrior::LateUpdate()
{
	Super::LateUpdate();
}
