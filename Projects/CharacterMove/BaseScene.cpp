#include "pch.h"
#include "BaseScene.h"
#include "CameraMove.h"
#include "LavaFlow.h"
#include "StruectedLavaSprite.h"
#include "LayerSplatter.h"
#include "engine\Utils.h"
#include "CameraMove.h"
#include "engine\HeightGetter.h"
#include "engine\Utils.h"
#include "engine/Warrior.h"
#include "engine/CoreHound.h"
#include "engine/SphereCollider.h"

void BaseScene::Init()
{
	//리소스 매니저 초기화
	MANAGER_RESOURCES()->Init();
	{
		_shader = make_shared<Shader>(L"Instancing.fx");
		MANAGER_RESOURCES()->AddResource(L"Default", _shader);
		wstring dTex = RESOURCES_ADDR_TEXTURE;
		dTex += L"Effect/noise.png";
		_dissolve = MANAGER_RESOURCES()->GetOrAddTexture(L"Dissolve", dTex);
	}

	//light
	{
		auto light = make_shared<GameObject>();
		light->AddComponent(make_shared<Light>());
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.1f);
		lightDesc.direction = Vec3(-0.5f, -0.5f, 0.0f);
		light->GetLight()->SetLightDesc(lightDesc);
		MANAGER_SCENE()->GetCurrentScene()->Add(light);
	}

	//Camera
	{
		frustom = make_shared<FrustomCamera>();
		_childCamera = make_shared<GameObject>();
		_childCamera->Awake();
		_childCamera->GetTransform()->SetLocalPosition(Vec3(0.f, 500.f, -1000.f));
		_childCamera->AddComponent(make_shared<Camera>());
		_childCamera->GetCamera()->SetCameraType(CameraType::Target);
		_childCamera->AddComponent(frustom);
		_childCamera->Start();
		_childCamera->SetName(L"Camera");
		MANAGER_SCENE()->GetCurrentScene()->Add(_childCamera);
	}

	{
		auto obj = make_shared<GameObject>();
		LavaSpriteDesc descs{};
		descs.duration = 10;
		descs.ShaderName = L"Lavashader";
		descs.ShaderPath = L"lava.fx";
		for (int i = 1; i < 31; i++) {
			descs.spritePathList.push_back(wstring(RESOURCES_ADDR_TEXTURE) + L"lava/lava." + to_wstring(i) + L".png");
		}
		obj->GetOrAddTransform()->SetLocalPosition(Vec3(0, 0.5f, 0));
		obj->AddComponent(make_shared<MeshRenderer>());
		shared_ptr<StruectedLavaSprite> sprite = make_shared<StruectedLavaSprite>(descs);
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->CreateGridWithDistance(3, 3, 4096);
		MANAGER_RESOURCES()->AddResource(L"lava", mesh);
		obj->GetMeshRenderer()->SetMesh(mesh);
		obj->GetMeshRenderer()->SetMaterial(MANAGER_RESOURCES()->GetResource<Material>(L"Veigar"));
		obj->GetMeshRenderer()->SetPass(0);
		obj->AddComponent(sprite);
		obj->AddComponent(make_shared<Lava>(100, 3, false));
		MANAGER_SCENE()->GetCurrentScene()->Add(obj);
	}

	{
		SkyBoxDesc descs{};
		descs.resourceFilePath[SkyBoxDesc::SKY_Front] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.resourceFilePath[SkyBoxDesc::SKY_Back] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.resourceFilePath[SkyBoxDesc::SKY_Right] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.resourceFilePath[SkyBoxDesc::SKY_Left] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.resourceFilePath[SkyBoxDesc::SKY_UP] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.resourceFilePath[SkyBoxDesc::SKY_DOWN] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsrock01.png";
		descs.shaderPath = L"skyBox.fx";
		skyBox = make_shared < Skybox>();
		skyBox->Set(&descs);
		skyBox->Start();

	}

	HeightPlainInfo heightMapDesc;
	heightMapDesc.heightFilename = L"HeightMap";
	heightMapDesc.heightFilePath = wstring(RESOURCES_ADDR_TEXTURE) + L"test.bmp";
	heightMapDesc.shaderFilePath = L"ShadowSplattingMapping.fx";
	//heightMapDesc.shaderFilePath = L"TerrainMapping.fx";
	heightMapDesc.shaderFilename = L"HeightMapShader";
	heightMapDesc.textureFilename = L"HeightMapTexture";
	heightMapDesc.textureFilePath = wstring(RESOURCES_ADDR_TEXTURE) + L"020.bmp";
	heightMapDesc.meshKey = L"TerrainMesh";
	heightMapDesc.distance = 1;
	heightMapDesc.row = 253;
	heightMapDesc.col = 253;

	_terrain = make_shared<Terrain>(heightMapDesc);
	_terrain->Awake();
	_terrain->AddComponent(make_shared<MeshRenderer>());
	_terrain->Start();
	quadTreeTerrain = make_shared<QuadTreeTerrain>();
	quadTreeTerrain->Set(_terrain, 3);
	quadTreeTerrain->Start();

	SplatterDesc spDesc{};
	spDesc.texPath[0] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsash01.png";
	spDesc.texPath[1] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppsashcracks.png";
	spDesc.texPath[2] = wstring(RESOURCES_ADDR_TEXTURE) + L"burningsteppscharcoal01.png";
	spDesc.texName[0] = L"Splat1";
	spDesc.texName[1] = L"Splat2";
	spDesc.texName[2] = L"Splat3";
	spDesc.alphaPath = wstring(RESOURCES_ADDR_TEXTURE) + L"testalpha.bmp";
	spDesc.alphaName = L"SplatAlpha";
	splatter = make_shared<LayerSplatter>();
	splatter->Set(spDesc, MANAGER_RESOURCES()->GetResource<Shader>(L"HeightMapShader"));
	quadTreeTerrain->AddSplatter(splatter);
	SetTerrain(_terrain);

	//Character
	{
		_warrior = make_shared<Warrior>();
		_warrior->Awake();
		_warrior->AddChild(_childCamera);
		_warrior->AddComponent(make_shared<PlayerController>());
		_warrior->Start();

		Add(_warrior);
		AddShadow(_warrior);
	}

#pragma region Client Thread
	_service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,
		1);

	ASSERT_CRASH(_service->Start());

	for (int32 i = 0; i < 3; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					_service->GetIocpCore()->Dispatch();
				}
			}
		);
	}
#pragma endregion Client Thread
}
void BaseScene::Start()
{
	Scene::Start();
}

void BaseScene::Update()
{
	quadTreeTerrain->Frame((*frustom->frustomBox.get()));
	MANAGER_SHADOW()->StartShadow();
	_terrain->GetMeshRenderer()->SetPass(1);
	_terrain->GetMeshRenderer()->ShadowUpdate();
	_terrain->GetMeshRenderer()->SetPass(0);

	Scene::ShadowUpdate();
	MANAGER_SHADOW()->EndShadow();

	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::PrintScreen))
	{
		Utils::ScreenShot(DC(), L"");
	}

	{
		sendInfo._uid = ClientPacketHandler::Instance().GetUserInfo()._uid;
		sendInfo._pos = _warrior->GetTransform()->GetPosition();
		sendInfo._isOnline = true;
		sendInfo._Rotate = _warrior->GetTransform()->GetLocalRotation();
		sendInfo._jumpFlag = *_warrior->GetComponent<PlayerController>()->GetJumpState();
		sendInfo._isAttack = _warrior->GetComponent<PlayerController>()->IsAttack();
		sendInfo._isBattle = _warrior->GetComponent<PlayerController>()->IsBattle();
		sendInfo._animState = *_warrior->GetComponent<PlayerController>()->GetCurrentUnitState();

		//Attack
		if (sendInfo._isAttack)
		{
			uint32 targetId = _warrior->GetComponent<PlayerController>()->GetPickedInfo()._instanceId;
			_sendBuffer = ClientPacketHandler::Instance().Make_BATTLE(sendInfo, targetId);
			_service->Broadcast(_sendBuffer);
		}

		//SendBuffer
		_sendBuffer = ClientPacketHandler::Instance().Make_USER_INFO(sendInfo);
	}

	SpawnManager::GetInstance().Update();

#pragma region Client Thread
	//12분의1초 = 83.33ms
	//30분의1초 = 33.33ms
	//60분의1초 = 16.67ms

	if (_threadTimer < 0.1f)
	{
		_threadTimer += MANAGER_TIME()->GetDeltaTime();
	}
	else
	{
		if (_sendBuffer != nullptr)
		{
			_service->Broadcast(_sendBuffer);
		}
		_threadTimer = 0.0f;
	}
#pragma endregion Client Thread

	//채팅
	if (MANAGER_IMGUI()->GetLatestMessages().size() > 0 && (MANAGER_IMGUI()->GetLatestMessages().size() != latestMessageSize))
	{
		string text = MANAGER_IMGUI()->GetLatestMessages().back();
		const char* newMessage = text.c_str();
		MESSAGE message;
		std::strncpy(message._messageBox, newMessage, sizeof(message._messageBox) - 1);
		message._messageBox[sizeof(message._messageBox) - 1] = '\0'; // Null 문자 추가
		_sendBuffer = ClientPacketHandler::Instance().Make_MESSAGE(message);
		_service->Broadcast(_sendBuffer);
	}
	latestMessageSize = MANAGER_IMGUI()->GetLatestMessages().size();

	Scene::Update();
	skyBox->Update();
	quadTreeTerrain->Update();
}

void BaseScene::LateUpdate()
{
	Scene::LateUpdate();
}
