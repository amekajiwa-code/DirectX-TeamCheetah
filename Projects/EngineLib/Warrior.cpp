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
		shared_ptr<Model> temp_model = make_shared<Model>();
		{
			wstring _modelAdr = RESOURCES_ADDR_MESH_SKELETAL;
			_modelAdr += L"BlackCow/BlackCow.mesh";
			temp_model->ReadModel(_modelAdr);
			wstring _modelMatrial = RESOURCES_ADDR_TEXTURE_SKELETAL;
			_modelMatrial += L"BlackCow/BlackCow.xml";
			temp_model->ReadMaterial(_modelMatrial);

			{
				wstring stand = RESOURCES_ADDR_ANIMATION;
				stand += L"BlackCow/Stand.anim";
				temp_model->ReadAnimation(stand);
				wstring forntWalk = RESOURCES_ADDR_ANIMATION;
				forntWalk += L"BlackCow/FrontWalk.anim";
				temp_model->ReadAnimation(forntWalk);
				wstring backWalk = RESOURCES_ADDR_ANIMATION;
				backWalk += L"BlackCow/BackWalk.anim";
				temp_model->ReadAnimation(backWalk);
				wstring frontRun = RESOURCES_ADDR_ANIMATION;
				frontRun += L"BlackCow/FrontRun.anim";
				temp_model->ReadAnimation(frontRun);
				wstring backRun = RESOURCES_ADDR_ANIMATION;
				backRun += L"BlackCow/BackRun.anim";
				temp_model->ReadAnimation(backRun);
				wstring jumpStart = RESOURCES_ADDR_ANIMATION;
				jumpStart += L"BlackCow/JumpStart.anim";
				temp_model->ReadAnimation(jumpStart);
				wstring jumpFall = RESOURCES_ADDR_ANIMATION;
				jumpFall += L"BlackCow/JumpFall.anim";
				temp_model->ReadAnimation(jumpFall);
				wstring jumpEnd = RESOURCES_ADDR_ANIMATION;
				jumpEnd += L"BlackCow/JumpEnd.anim";
				temp_model->ReadAnimation(jumpEnd);
				wstring jumpEndRun = RESOURCES_ADDR_ANIMATION;
				jumpEndRun += L"BlackCow/JumpEndRun.anim";
				temp_model->ReadAnimation(jumpEndRun);
			}

		}
		const auto& shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		shared_ptr<ModelRenderer> tempRenderer = make_shared<ModelRenderer>(shader);
		{
			tempRenderer->SetModel(temp_model);
			tempRenderer->SetPass(1);
		}
		shared_ptr<ModelAnimator> tempAnimator = make_shared<ModelAnimator>();
		{
			tempAnimator->SetPlay(true);
			tempAnimator->SetLoop(true);
		}
		_childModel->Awake();
		_childModel->AddComponent(tempRenderer);
		_childModel->AddComponent(tempAnimator);
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
