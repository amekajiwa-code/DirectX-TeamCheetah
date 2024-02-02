#include "pch.h"
#include "Warrior.h"
#include "PlayerController.h"

Warrior::Warrior()
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();
	_objType = ObjectType::Unit;
}

Warrior::~Warrior()
{
}

void Warrior::CharacterInit()
{
	_childCamera = make_shared<GameObject>();
	_childModel = make_shared<GameObject>();

	//Camera
	{
		_childCamera->Awake();
		_childCamera->GetTransform()->SetLocalPosition(Vec3(0.f, 500.f, -1000.f));
		_childCamera->AddComponent(make_shared<Camera>());
		_childCamera->GetCamera()->SetCameraType(CameraType::Target);
		_childCamera->Start();
		_childCamera->SetName(L"Camera");
	}
	//Character
	{
		shared_ptr<Model> model = make_shared<Model>();
		{
			AddModelAndMaterial(model, L"BlackCow");
			AddAnimation(model, L"BlackCow", L"Stand");
			AddAnimation(model, L"BlackCow", L"FrontWalk");
			AddAnimation(model, L"BlackCow", L"BackWalk");
			AddAnimation(model, L"BlackCow", L"FrontRun");
			AddAnimation(model, L"BlackCow", L"BackRun");
			AddAnimation(model, L"BlackCow", L"JumpStart");
			AddAnimation(model, L"BlackCow", L"JumpFall");
			AddAnimation(model, L"BlackCow", L"JumpEnd");
			AddAnimation(model, L"BlackCow", L"JumpEndRun");
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

		Vec3 rot = _childModel->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		_childModel->GetTransform()->SetLocalRotation(rot);
	}

	SetName(L"Warrior");
	AddChild(_childModel);
	AddChild(_childCamera);
	_controller = make_shared<PlayerController>();
	AddComponent(_controller);
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
