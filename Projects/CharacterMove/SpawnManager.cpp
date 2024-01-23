#include "pch.h"
#include "SpawnManager.h"
#include "AIController.h"

using namespace std::chrono;

Vec3 interpolate(double alpha, Vec3 targetPos, Vec3 prePos) {
	// ���� ������ ���� ���� ��ġ ���
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
	_chr->GetTransform()->SetPosition(spawnPos);

	_otherPlayers.insert(std::make_pair(uid, _chr)); //map�� �𵨰� �ĺ�id �߰�
}

void SpawnManager::SpawnOtherPlayers()
{
	for (const auto& pair : ClientPacketHandler::Instance().GetOtherUserInfoMap()) {
		//�ٸ��÷��̾� ��ġ ����ȭ
		auto it = _otherPlayers.find(pair.first);
		// it : first : uint64 / second : shared_ptr<LSkinningModel>
		if (it != _otherPlayers.end())
		{
			// �ٸ��÷��̾ �̹� �ִ�.
			if (pair.second._isOnline == false)
			{
				//�������� �ƴ϶�� �ٸ��÷��̾� ��Ͽ��� ����
				_otherPlayers.erase(it);
				ClientPacketHandler::Instance().EraseOtherUserInfoMap(pair.first);
				//���� : �̰� ������ ���ķ� �� �ǵ�� nullptr ��ɷ� �����
			}
			else
			{
				// ������ ���� �ð� ��� (0.0���� 1.0 ������ ��)
				auto calcTime = high_resolution_clock::now() - seconds(static_cast<int>(pair.second._timeStamp));
				auto durationSec = duration_cast<duration<double>>(calcTime.time_since_epoch()).count();
				double alpha = fmin(1.0, durationSec / 1.0);
				Vec3 target = pair.second._pos;
				Vec3 pos = it->second->GetTransform()->GetPosition();
				Vec3 rot = it->second->GetTransform()->GetLocalRotation();

				if (pair.second._animState != PlayerAnimState::Idle)
				{
					Vec3 direction = target - pos;
					pos += interpolate(alpha, direction, Vec3(0.0f, 0.0f, 0.0f)) * pair.second._moveSpeed * MANAGER_TIME()->GetDeltaTime();
				}

				//ȸ�� ���� ���
				Vec3 targetRot = pair.second._Rotate;
				/*Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
				Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(targetRot.y, 0.0f, 0.0f);
				Quaternion calcRot = Quaternion::Slerp(startRotation, endRotation, 0.2);
				rot.y = QuatToEulerAngleY(calcRot);*/

				it->second->GetTransform()->SetPosition(pos);
				it->second->GetTransform()->SetLocalRotation(targetRot);
				it->second->GetComponent<AIController>()->SetAnimState(pair.second._animState);
			}
		}
		else
		{
			//�ٸ��÷��̾� ó�� ����� ����
			SpawnOtherPlayer(pair.first, pair.second._pos);
			cout << "find not key, new player spawn" << endl;
		}
	}
}

void SpawnManager::SpawnMonsters()
{
	for (const auto& pair : ClientPacketHandler::Instance().GetCharaInfoList())
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

		auto it = _monsters.find(pair.first);
		if (it != _monsters.end())
		{
			Vec3 pos = it->second->GetTransform()->GetPosition();
			// ���� ��ġ�� ��ǥ ��ġ�� ���� ���
			Vec3 dv = pair.second._nextPos - pos;
			// ���� ������ ���� �ε巴�� ���� ��ġ ������Ʈ
			float speed = 1.0f;
			pos += dv * speed * MANAGER_TIME()->GetDeltaTime();
			it->second->GetTransform()->SetPosition(pos);
		}
		else
		{
			_chr->GetTransform()->SetPosition(pair.second._pos);
			_monsters.insert(make_pair(pair.first, _chr));
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
			pair.second->FixedUpdate();
			pair.second->Update();
			pair.second->LateUpdate();
		}
	}*/
}