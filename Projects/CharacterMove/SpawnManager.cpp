#include "pch.h"
#include "SpawnManager.h"
#include "AIController.h"

using namespace std::chrono;

Vec3 interpolate(double alpha, Vec3 targetPos, Vec3 prePos) {
	// 선형 보간을 통한 실제 위치 계산
	float interpolatedX = (1.0 - alpha) * prePos.x + alpha * targetPos.x;
	float interpolatedY = (1.0 - alpha) * prePos.y + alpha * targetPos.y;
	float interpolatedZ = (1.0 - alpha) * prePos.z + alpha * targetPos.z;

	return Vec3{ interpolatedX, interpolatedY, interpolatedZ };
}

float QuatToEulerAngleY(Quaternion q)
{
	Vec3 angle;

	//y pitch
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angle.y = std::atan2(sinp, cosp) - PI;

	return angle.y;
}

void SpawnManager::SpawnOtherPlayer(uint64 uid, Vec3 spawnPos)
{
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

	shared_ptr<Character> _chr = make_shared<Player>();
	_chr->SetName(L"BlackCow");
	_chr->AddComponent(make_shared<AIController>());
	_chr->Awake();
	_chr->AddChild(cow);
	_chr->Start();
	_chr->GetTransform()->SetScale(Vec3(0.1f));
	_chr->GetTransform()->SetPosition(spawnPos);

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
				// 보간을 위한 시간 계산 (0.0에서 1.0 사이의 값)
				auto calcTime = high_resolution_clock::now() - seconds(static_cast<int>(pair.second._timeStamp));
				auto durationSec = duration_cast<duration<double>>(calcTime.time_since_epoch()).count();
				double alpha = fmin(1.0, durationSec / 1.0);
				Vec3 target = pair.second._pos;
				Vec3 pos = it->second->GetTransform()->GetPosition();
				Vec3 rot = it->second->GetTransform()->GetLocalRotation();

				Vec3 direction = target - pos;
				pos += interpolate(alpha, direction, Vec3(0.0f, 0.0f, 0.0f)) * pair.second._moveSpeed * MANAGER_TIME()->GetDeltaTime();

				//회전 보간 계산
				Vec3 targetRot = pair.second._Rotate;
				Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
				Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(targetRot.y, 0.0f, 0.0f);
				Quaternion calcRot = Quaternion::Slerp(startRotation, endRotation, alpha);
				rot.y = QuatToEulerAngleY(calcRot);

				it->second->GetTransform()->SetPosition(pos);
				it->second->GetTransform()->SetLocalRotation(targetRot);
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

void SpawnManager::SpawnMonster(uint64 uid, Vec3 spawnPos)
{
#pragma region Initialize
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

	shared_ptr<Character> _chr = make_shared<Character>();
	_chr->SetName(L"BlackCow");
	_chr->AddComponent(make_shared<AIController>());
	_chr->Awake();
	_chr->AddChild(cow);
	_chr->Start();
	_chr->GetTransform()->SetScale(Vec3(0.1f));
	_chr->GetTransform()->SetPosition(spawnPos);
#pragma endregion

	_monsters.insert(make_pair(uid, _chr));
}

void SpawnManager::SpawnMonsters()
{
	for (const auto& pair : ClientPacketHandler::Instance().GetMobInfoList()) {
		//다른플레이어 위치 동기화
		auto it = _monsters.find(pair.first);
		// it : first : uint64 / second : shared_ptr<LSkinningModel>
		if (it != _monsters.end())
		{
			// 다른플레이어가 이미 있다.
			if (pair.second._isAlive == false)
			{
				_monsters.erase(it);
				ClientPacketHandler::Instance().EraseMonster(pair.first);
				//주의 : 이거 삭제한 이후로 얘 건들면 nullptr 뜰걸로 예상됨
			}
			else
			{
				// 보간을 위한 시간 계산 (0.0에서 1.0 사이의 값)
				auto calcTime = high_resolution_clock::now() - seconds(static_cast<int>(pair.second._timeStamp));
				auto durationSec = duration_cast<duration<double>>(calcTime.time_since_epoch()).count();
				double alpha = fmin(1.0, durationSec / 1.0);
				Vec3 target = pair.second._pos;
				Vec3 pos = it->second->GetTransform()->GetPosition();
				Vec3 rot = it->second->GetTransform()->GetLocalRotation();

				Vec3 direction = target - pos;
				pos += interpolate(alpha, Vec3{ direction.x, 0.0f, direction.z }, Vec3(0.0f, 0.0f, 0.0f)) * (pair.second._moveSpeed / 2) * MANAGER_TIME()->GetDeltaTime();

				//회전 보간 계산
				Vec3 targetRot = pair.second._Rotate;
				Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
				Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(targetRot.y, 0.0f, 0.0f);
				Quaternion calcRot = Quaternion::Slerp(startRotation, endRotation, alpha);
				rot.y = QuatToEulerAngleY(calcRot);

				it->second->GetTransform()->SetPosition(pos);
				it->second->GetTransform()->SetLocalRotation(targetRot);
				it->second->GetComponent<AIController>()->SetAnimState(pair.second._animState);
			}
		}
		else
		{
			//다른플레이어 처음 등장시 스폰
			SpawnMonster(pair.first, pair.second._pos);
			cout << "find not key, new monster spawn" << endl;
		}
	}
}

void SpawnManager::Update()
{
	SpawnOtherPlayers();
	SpawnMonsters(); // <-- 동작 중 메모리 누수 있음

	if (_otherPlayers.empty() == false)
	{
		for (const auto& pair : _otherPlayers)
		{
			pair.second->FixedUpdate();
			pair.second->Update();
			pair.second->LateUpdate();
			
		}
	}

	if (_monsters.empty() == false)
	{
		for (const auto& pair : _monsters)
		{
			pair.second->FixedUpdate();
			pair.second->Update();
			pair.second->LateUpdate();
		}
	}
}
