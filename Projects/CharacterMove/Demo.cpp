#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	//리소스 매니저 초기화
	MANAGER_RESOURCES()->Init();
	{
		_shader = make_shared<Shader>(L"GameObject.fx");
		MANAGER_RESOURCES()->AddResource<Shader>(L"Default", _shader);
	}
	//랜더 매니저 초기화
	MANAGER_RENDERER()->Init(_shader);
	//Camera
	{
		_camera = make_shared<GameObject>();
		_camera->Awake();
		_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -50.f));
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraMove>());
	}
	//light
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.diffuse = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.specular = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.direction = Vec3(1.f, -1.f, -1.f);
		MANAGER_RENDERER()->PushLightData(lightDesc);
	}
	//Character
	{
		shared_ptr<Model> tempModel = make_shared<Model>();
		{
			wstring modelAdr = RESOURCES_ADDR_MESH_SKELETAL;
			modelAdr += L"BlackCow/BlackCow.mesh";
			tempModel->ReadModel(modelAdr);
			wstring modelMatrial = RESOURCES_ADDR_TEXTURE_SKELETAL;
			modelMatrial += L"BlackCow/BlackCow.xml";
			tempModel->ReadMaterial(modelMatrial);
			wstring modelAnimation = RESOURCES_ADDR_ANIMATION;
			modelAnimation += L"BlackCow/Stand.anim";
			tempModel->ReadAnimation(modelAnimation);
		}
		shared_ptr<ModelRenderer> tempRenderer = make_shared<ModelRenderer>(_shader);
		{
			tempRenderer->SetModel(tempModel);
			tempRenderer->SetPass(1);
		}
		shared_ptr<ModelAnimator> tempAnimator = make_shared<ModelAnimator>();
		{
			tempAnimator->SetPlay(true);
			tempAnimator->SetLoop(true);
		}
		shared_ptr<GameObject> cow = make_shared<GameObject>();
		cow->AddComponent(tempRenderer);
		cow->AddComponent(tempAnimator);
		cow->Awake();
		Vec3 rot = cow->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		cow->GetTransform()->SetLocalRotation(rot);

		_chr = make_shared<GameObject>();
		_chr->Awake();
		_chr->AddChild(cow);
		_chr->GetTransform()->SetScale(Vec3(0.1f));
	}
}

void Demo::Update()
{
	_camera->Update();
	MANAGER_RENDERER()->Update();

	{
		Vec3 look = _chr->GetTransform()->GetLookVector();
		Vec3 tf = _chr->GetTransform()->GetPosition();
		tf += look * 100.f * MANAGER_TIME()->GetDeltaTime();

		_chr->GetTransform()->SetPosition(tf);

		_chr->FixedUpdate();
		_chr->Update();
		_chr->LateUpdate();

	}
}

void Demo::Render()
{
}
