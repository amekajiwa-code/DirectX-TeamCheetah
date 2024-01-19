#include "pch.h"
#include "SpawnManager.h"
#include "AIController.h"

void SpawnManager::SpawnOtherPlayer(uint64 uid, Vec3 spawnPos)
{
	shared_ptr<Character> _chr = make_shared<Character>();
	shared_ptr<Shader> _shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");

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
	_chr->AddComponent(make_shared<AIController>());
	_chr->Awake();
	_chr->AddChild(cow);
	_chr->Start();
	_chr->GetTransform()->SetScale(Vec3(0.1f));

	_otherPlayers.insert(std::make_pair(uid, _chr)); //map에 모델과 식별id 추가
}

void SpawnManager::SpawnOtherPlayers()
{
	for (const auto& pair : ClientPacketHandler::Instance().GetOtherUserInfoMap()) {
		//다른플레이어 위치 동기화
		auto it = _otherPlayers.find(pair.first);
		// it : first : uint64 / second : shared_ptr<LSkinningModel>
		if (it != _otherPlayers.end())
		{
			// 다른플레이어가 이미 있다.
			if (pair.second._isOnline == false)
			{
				//접속중이 아니라면 다른플레이어 목록에서 삭제
				_otherPlayers.erase(it);
				ClientPacketHandler::Instance().EraseOtherUserInfoMap(pair.first);
				//주의 : 이거 삭제한 이후로 얘 건들면 nullptr 뜰걸로 예상됨
			}
			else
			{
				float interp = 1.0f;  // 보간 강도 조절
				Vec3 pos = it->second->GetTransform()->GetPosition();
				// 현재 위치와 목표 위치의 차이 계산
				Vec3 dv = pair.second._pos - it->second->GetTransform()->GetPosition();
				// 선형 보간을 통해 부드럽게 현재 위치 업데이트
				pos += dv * pair.second._moveSpeed * MANAGER_TIME()->GetDeltaTime();
				it->second->GetTransform()->SetPosition(pos);
				it->second->GetTransform()->SetLocalRotation(pair.second._Rotate);
				it->second->GetComponent<AIController>()->SetAnimState(pair.second._animState);
			}
		}
		else
		{
			//다른플레이어 처음 등장시 스폰
			SpawnOtherPlayer(pair.first, pair.second._pos);
			cout << "find not key, new player spawn" << endl;
		}
	}
}

void SpawnManager::SpawnMonsters()
{
	for (const auto& pair : ClientPacketHandler::Instance().GetCharaInfoList())
	{
		shared_ptr<Character> mob = make_shared<Character>();
		mob->Awake();
		mob->AddComponent(make_shared<MeshRenderer>());
		//Mesh Set
		{
			auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Cube");
			mob->GetMeshRenderer()->SetMesh(mesh);
		}
		//Material Set
		{
			//특정 오브젝트의 머티리얼 변경시 Clone을 통해 인스턴싱을 해야함 (꼭)
			//하지 않을 경우 원본이 오염된다.
			auto material = MANAGER_RESOURCES()->GetResource<Material>(L"Veigar")->Clone();
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(0.33f);
			desc.diffuse = Vec4(0.33f);

			mob->GetMeshRenderer()->SetMaterial(material);
		}

		auto it = _monsters.find(pair.first);
		if (it != _monsters.end())
		{
			Vec3 pos = it->second->GetTransform()->GetPosition();
			// 현재 위치와 목표 위치의 차이 계산
			Vec3 dv = pair.second._nextPos - pos;
			// 선형 보간을 통해 부드럽게 현재 위치 업데이트
			float speed = 1.0f;
			pos += dv * speed * MANAGER_TIME()->GetDeltaTime();
			it->second->GetTransform()->SetPosition(pos);
		}
		else
		{
			mob->GetTransform()->SetPosition(pair.second._pos);
			_monsters.insert(make_pair(pair.first, mob));
		}
	}
}

void SpawnManager::Update()
{
	SpawnOtherPlayers();
	//SpawnMonsters();

	if (_otherPlayers.empty() == false)
	{
		for (const auto& pair : _otherPlayers)
		{
			pair.second->FixedUpdate();
			pair.second->Update();
			pair.second->LateUpdate();
			
		}
	}

	/*if (_monsters.empty() == false)
	{
		for (const auto& pair : _monsters)
		{
			pair.second->Update();
		}
	}*/
}
