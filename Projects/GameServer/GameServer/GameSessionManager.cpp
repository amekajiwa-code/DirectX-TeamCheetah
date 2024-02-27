#include "pch.h"
#include "GameSessionManager.h"

GameSessionManager GSessionManager;
bool isUpdate = true;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	//새 유저 등록
	Player_INFO userInfo; 
	userInfo._uid = sessionIdCount; //session에 배정된 id send
	userInfo._pos = { 0.f, 0.f, 0.f };
	userInfo._isOnline = true;
	_userInfoList.insert(make_pair(sessionIdCount, userInfo));
	SendBufferRef sendBuffer = ServerPacketHandler::Make_USER_INFO(userInfo, false);
	session->Send(sendBuffer);
	session->SetSessionId(sessionIdCount++);
	_sessions.insert(session);
}

void GameSessionManager::Remove(GameSessionRef session)
{
	WRITE_LOCK;
	auto it = _userInfoList.find(session->GetSessionId());
	if (it != _userInfoList.end())
	{
		_userInfoList.erase(it);
	}
	
	SendBufferRef sendBuffer = ServerPacketHandler::Make_USER_DISCONNECT(session->GetSessionId());
	Broadcast(sendBuffer);
	_sessions.erase(session);
}

void GameSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}

void GameSessionManager::UpdateUserInfo(Player_INFO info)
{
	auto it = _userInfoList.find(info._uid);
	if (it != _userInfoList.end())
	{
		it->second = info;
	}
}

void GameSessionManager::GenerateMobList()
{
	// 랜덤 숫자 생성기 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distributionX(-450, -200.0f);
	std::uniform_real_distribution<float> distributionY(300, 350.0f);

	for (int id = 0; id < 2; ++id)
	{
		MONSTER_INFO c0;

		// 지정된 범위 내에서 x 및 z에 대한 무작위 값 설정
		c0._instanceId = id;
		c0._pos = { distributionX(gen), 25.0f, distributionY(gen) };
		cout << "x : " << c0._pos.x << ", z : " << c0._pos.z << endl;

		_mobInfoList.insert(make_pair(id, c0));
	}
}

void GameSessionManager::UpdateMobInfo(MONSTER_INFO info)
{
	auto it = _mobInfoList.find(info._instanceId);
	if (it != _mobInfoList.end())
	{
		it->second = info;
	}
}

void GameSessionManager::EnemyIsAttack(Player_INFO& target, MONSTER_INFO& enemy)
{
	WRITE_LOCK
	if (attackTimer > attackTime)
	{
		if (enemy._atk >= target._hp) //막타
		{
			target._hp = 0;
			target._isAlive = false;
		}
		else
		{
			target._hp -= enemy._atk;
		}

		for (const auto& session : GSessionManager.GetSessionsRef()) {
			if (session->GetSessionId() == target._uid)
			{
				cout << "attack for " << target._uid << endl;
				SendBufferRef sendbuffer = ServerPacketHandler::Make_USER_INFO(target, false);
				session->Send(sendbuffer);
				break;
			}
		}

		attackTimer = 0.0f;
	}
	else
	{
		attackTimer += TIMER().getDeltaTime();
	}
}
