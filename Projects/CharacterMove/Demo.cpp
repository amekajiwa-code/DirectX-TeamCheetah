#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"
#include "PlayerController.h"
#include "engine\Utils.h"

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
		_camera->GetTransform()->SetLocalPosition(Vec3(0.f, 500.f, -1000.f));
		_camera->AddComponent(make_shared<Camera>());
		_camera->GetCamera()->SetCameraType(CameraType::Target);
		_camera->SetName(L"Camera");
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
		cow->Start();

		Vec3 rot = cow->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		cow->GetTransform()->SetLocalRotation(rot);

		_chr = make_shared<GameObject>();
		_chr->SetName(L"BlackCow");
		_chr->AddComponent(make_shared<PlayerController>());
		_chr->Awake();
		_chr->AddChild(cow);
		_chr->AddChild(_camera);
		_chr->Start();
		_chr->GetTransform()->SetScale(Vec3(0.1f));
	}

	//Plane
	{
		_map = make_shared<GameObject>();
		_map->Awake();

		{
			shared_ptr<Mesh> plane = make_shared<Mesh>();
			plane->CreateQuad();
			shared_ptr<Material> mtrl = make_shared<Material>();
			mtrl->SetShader(_shader);
			wstring tex = RESOURCES_ADDR_TEXTURE;
			tex += L"grass.jpg";
			shared_ptr<Texture> grass = make_shared<Texture>();
			grass->Load(tex);
			mtrl->SetDiffuseMap(grass);

			shared_ptr<MeshRenderer> _renderer = make_shared<MeshRenderer>();
			_renderer->SetMesh(plane);
			_renderer->SetMaterial(mtrl);
			_map->AddComponent(_renderer);
		}
		_map->GetTransform()->SetScale(Vec3(100, 100, 1));

		Vec3 rot = _map->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		_map->GetTransform()->SetRotation(rot);
	}
}

void Demo::Update()
{
	MANAGER_RENDERER()->Update();

	{
		_chr->FixedUpdate();
		_chr->Update();
		_chr->LateUpdate();
	}

	{
		_map->Update();
	}

	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::PrintScreen))
	{
		Utils::ScreenShot(DC(),L"");
	}
}

void Demo::Render()
{
}
