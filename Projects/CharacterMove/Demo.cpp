#include "pch.h"
#include "Demo.h"


void Demo::Init(){

	shared_ptr<BaseScene> scene = make_shared<BaseScene>();
	MANAGER_SCENE()->ChangeScene(scene);

//	//리소스 매니저 초기화
//	MANAGER_RESOURCES()->Init();
//	{
//		_shader = make_shared<Shader>(L"TweenAnimation.fx");
//		MANAGER_RESOURCES()->AddResource<Shader>(L"Default", _shader);
//		wstring dTex = RESOURCES_ADDR_TEXTURE;
//		dTex += L"Effect/noise.png";
//		_dissolve = MANAGER_RESOURCES()->GetOrAddTexture(L"Dissolve", dTex);
//	}
//
//	//랜더 매니저 초기화
//	MANAGER_RENDERER()->Init(_shader);
//
//	//light
//	{
//		LightDesc lightDesc;
//		lightDesc.ambient = Vec4(1.f, 1.f, 1.f, 1.0f);
//		lightDesc.diffuse = Vec4(1.f, 1.f, 1.f, 0.5f);
//		lightDesc.specular = Vec4(1.0, 1.0f, 1.0f, 1.0f);
//
//		{
//			Transform tf;
//			Vec3 rv(0.f);
//			rv.x += ::XMConvertToRadians(45.f);
//			rv.y += ::XMConvertToRadians(90.f);
//			rv.z = 0;
//			tf.SetRotation(rv);
//			tf.UpdateTransform();
//			Vec3 sundir = tf.GetLookVector();
//			sundir.Normalize();
//			lightDesc.direction = sundir;
//		}
//
//		MANAGER_RENDERER()->PushLightData(lightDesc);
//	}
//
//	//Plane
//	{
//		_map = make_shared<GameObject>();
//		_map->Awake();
//		{
//			shared_ptr<Mesh> plane = make_shared<Mesh>();
//			plane->CreateQuad();
//			shared_ptr<Material> mtrl = make_shared<Material>();
//			_terShader = make_shared<Shader>(L"GameTerrain.fx");
//			mtrl->SetShader(_terShader);
//
//			wstring tex = RESOURCES_ADDR_TEXTURE;
//			tex += L"grass.jpg";
//			shared_ptr<Texture> grass = make_shared<Texture>();
//			grass->Load(tex);
//
//			{
//				MaterialDesc desc;
//				desc.ambient = Color(1.0f,1.0f,1.0f,1.0f);
//				mtrl->SetMaterialDesc(desc);
//			}
//
//			mtrl->SetDiffuseMap(grass);
//			mtrl->SetNormalMap(nullptr);
//
//			shared_ptr<MeshRenderer> _renderer = make_shared<MeshRenderer>();
//			_renderer->SetMesh(plane);
//			_renderer->SetMaterial(mtrl);
//			_map->AddComponent(_renderer);
//		}
//		_map->Start();
//		_map->GetTransform()->SetScale(Vec3(100, 100, 1));
//
//		Vec3 rot = _map->GetTransform()->GetLocalRotation();
//		rot.x += ::XMConvertToRadians(90.f);
//		_map->GetTransform()->SetRotation(rot);
//	}
//
//	//Camera
//	{
//		_childCamera = make_shared<GameObject>();
//		_childCamera->Awake();
//		_childCamera->GetTransform()->SetLocalPosition(Vec3(0.f, 500.f, -1000.f));
//		_childCamera->AddComponent(make_shared<Camera>());
//		_childCamera->GetCamera()->SetCameraType(CameraType::Target);
//		_childCamera->Start();
//		_childCamera->SetName(L"Camera");
//	}
//
//	//Character
//	{
//		_warrior = make_shared<Warrior>();
//		_warrior->Awake();
//		_warrior->AddChild(_childCamera);
//		_warrior->AddComponent(make_shared<PlayerController>());
//		_warrior->Start();
//	}
//#pragma region Client Thread
//	this_thread::sleep_for(250ms);
//
//	_service = MakeShared<ClientService>(
//		NetAddress(L"127.0.0.1", 7777),
//		MakeShared<IocpCore>(),
//		MakeShared<ServerSession>,
//		1);
//
//	ASSERT_CRASH(_service->Start());
//
//	for (int32 i = 0; i < 3; i++)
//	{
//		GThreadManager->Launch([=]()
//			{
//				while (true)
//				{
//					_service->GetIocpCore()->Dispatch();
//				}
//			}
//		);
//	}
//#pragma endregion Client Thread
}

void Demo::Update()
{
//	MANAGER_RENDERER()->Update();
//	static float dt = 0.f;
//
//	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::KEY_1))
//	{
//		if (_isdisv)
//		{
//			_isdisv = false;
//		}
//		else
//		{
//			_isdisv = true;
//		}
//	}
//	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::KEY_2))
//	{
//		if (dt >= 1.0f)
//		{
//			dt = 0.f;
//		}
//
//		_isdisv = false;
//	}
//
//	if (_isdisv)
//	{
//		dt += MANAGER_TIME()->GetDeltaTime() * 0.35f;
//	}
//
//	_shader->GetSRV("dissolve")->SetResource(_dissolve->GetTexture().Get());
//	_shader->GetScalar("time")->SetFloat(dt);
//
//	{
//		_map->Update();
//	}
//
//	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::PrintScreen))
//	{
//		Utils::ScreenShot(DC(), L"");
//	}
//
//	{
//		_warrior->FixedUpdate();
//		_warrior->Update();
//		_warrior->LateUpdate();
//		Player_INFO sendInfo;
//		sendInfo._uid = ClientPacketHandler::Instance().GetUserInfo()._uid;
//		sendInfo._pos = _warrior->GetTransform()->GetPosition();
//		sendInfo._isOnline = true;
//		sendInfo._animState = *_warrior->GetComponent<PlayerController>()->GetCurrentUnitState();
//		sendInfo._Rotate = _warrior->GetTransform()->GetLocalRotation();
//		sendInfo._jumpFlag = *_warrior->GetComponent<PlayerController>()->GetJumpState();
//		//SendBuffer
//		_sendBuffer = ClientPacketHandler::Instance().Make_USER_INFO(sendInfo);
//	}
//
//	SpawnManager::GetInstance().Update();
//
//#pragma region Client Thread
//	//12분의1초 = 83.33ms
//	//30분의1초 = 33.33ms
//	//60분의1초 = 16.67ms
//
//	if (_threadTimer < 0.08333f)
//	{
//		_threadTimer += MANAGER_TIME()->GetDeltaTime();
//	}
//	else
//	{
//		if (_sendBuffer != nullptr)
//		{
//			_service->Broadcast(_sendBuffer);
//		}
//		_threadTimer = 0.0f;
//	}
//#pragma endregion Client Thread
}

void Demo::Render()
{
}
