#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"
#include "PlayerController.h"
#include "engine\Utils.h"

SendBufferRef GsendBuffer;

bool HasDifference(const Vec3& v1, const Vec3& v2, float tolerance = 0.0001f) {
	// 부동 소수점 비교를 위해 허용 가능한 오차 범위를 지정
	auto floatEquals = [tolerance](float a, float b) {
		return std::fabs(a - b) < tolerance;
		};

	// x, y, z 중에서 1.0f 이라도 차이가 나면 true를 반환
	if (!floatEquals(v1.x, v2.x) || !floatEquals(v1.y, v2.y) || !floatEquals(v1.z, v2.z)) {
		return true;
	}

	// 모든 차이가 허용 가능한 오차 범위 내에 있으면 false 반환
	return false;
}

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
		lightDesc.ambient = Vec4(1.f, 1.f, 1.f, 1.0f);
		lightDesc.diffuse = Vec4(1.f, 1.f, 1.f, 0.5f);
		lightDesc.specular = Vec4(1.0, 1.0f, 1.0f, 1.0f);

		{
			Transform tf;
			Vec3 rv(0.f);
			rv.x += ::XMConvertToRadians(45.f);
			rv.y += ::XMConvertToRadians(90.f);
			rv.z = 0;
			tf.SetRotation(rv);
			tf.UpdateTransform();
			Vec3 sundir = tf.GetLookVector();
			sundir.Normalize();
			lightDesc.direction = sundir;
		}

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

			wstring stand = RESOURCES_ADDR_ANIMATION;
			stand += L"BlackCow/Stand.anim";
			tempModel->ReadAnimation(stand);
			wstring run = RESOURCES_ADDR_ANIMATION;
			run += L"BlackCow/Run.anim";
			tempModel->ReadAnimation(run);
			wstring backRun = RESOURCES_ADDR_ANIMATION;
			backRun += L"BlackCow/BackRun.anim";
			tempModel->ReadAnimation(backRun);
			wstring jumpStart = RESOURCES_ADDR_ANIMATION;
			jumpStart += L"BlackCow/JumpStart.anim";
			tempModel->ReadAnimation(jumpStart);
			wstring jumpFall = RESOURCES_ADDR_ANIMATION;
			jumpFall += L"BlackCow/JumpFall.anim";
			tempModel->ReadAnimation(jumpFall);
			wstring jumpEnd = RESOURCES_ADDR_ANIMATION;
			jumpEnd += L"BlackCow/JumpEnd.anim";
			tempModel->ReadAnimation(jumpEnd);
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
		cow->SetName(L"Model");

		Vec3 rot = cow->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		cow->GetTransform()->SetLocalRotation(rot);

		_chr = make_shared<Player>();
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

#pragma region Client Thread
	this_thread::sleep_for(250ms);

	service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 3; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			}
		);
	}
#pragma endregion Client Thread
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

	//SpawnManager
	SpawnManager::GetInstance().Update();
	//SendBuffer
	Player_INFO sendInfo;
	sendInfo._uid = ClientPacketHandler::Instance().GetUserInfo()._uid;
	sendInfo._pos = _chr->GetTransform()->GetPosition();
	sendInfo._isOnline = true;
	sendInfo._animState = _chr->GetComponent<PlayerController>()->GetCurrentAnimState();
	sendInfo._Rotate = _chr->GetTransform()->GetLocalRotation();
	GsendBuffer = ClientPacketHandler::Instance().Make_USER_INFO(sendInfo);

#pragma region Client Thread
	//12분의1초 = 83.33ms
	//30분의1초 = 33.33ms
	//60분의1초 = 16.67ms

	if (ThreadTimer < 0.08333f)
	{
		ThreadTimer += MANAGER_TIME()->GetDeltaTime();
	}
	else
	{
		if (GsendBuffer != nullptr)
		{
			service->Broadcast(GsendBuffer);
		}
		ThreadTimer = 0.0f;
	}
#pragma endregion Client Thread
}

void Demo::Render()
{
}
