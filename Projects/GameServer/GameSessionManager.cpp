#include "pch.h"
#include "GameSessionManager.h"

GameSessionManager GSessionManager;
bool isUpdate = true;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	//session에 배정된 id send
	Player_INFO userInfo;
	userInfo._uid = sessionIdCount;
	userInfo._pos = { 0.f, 0.f, 0.f };
	userInfo._isOnline = true;
	_userInfoList.insert(make_pair(sessionIdCount, userInfo));
	SendBufferRef sendBuffer = ServerPacketHandler::Make_USER_INFO(userInfo, false);
	session->Send(sendBuffer);
	//session 정보 저장후 배열 추가
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

void GameSessionManager::GenerateCharaList()
{
	// 랜덤 숫자 생성기 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(-50.0f, 50.0f);

	for (int id = 0; id < 1; ++id)
	{
		CHARACTER_INFO c0;

		// 지정된 범위 내에서 x 및 z에 대한 무작위 값 설정
		c0._instanceId = id;
		c0._pos = { distribution(gen), 0.0f, distribution(gen) };
		cout << "x : " << c0._pos.x << ", z : " << c0._pos.z << endl;

		_charaInfoList.insert(make_pair(id, c0));
	}
}

void GameSessionManager::UpdateCharaInfo(CHARACTER_INFO info)
{
	auto it = _charaInfoList.find(info._instanceId);
	if (it != _charaInfoList.end())
	{
		it->second = info;
	}
}

float IsPlayerInRanger(const DirectX::XMFLOAT3& playerPos, const DirectX::XMFLOAT3& monsterPos)
{
	DirectX::XMVECTOR playerVec = DirectX::XMLoadFloat3(&playerPos);
	DirectX::XMVECTOR monsterVec = DirectX::XMLoadFloat3(&monsterPos);

	DirectX::XMVECTOR diff = DirectX::XMVectorSubtract(playerVec, monsterVec);
	float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(diff));

	return distance;
}

//TODO: 범위안에 있는놈중 가장 가까운놈 타겟으로 삼기
DirectX::XMFLOAT3 GameSessionManager::CalcNextPos(CHARACTER_INFO chara) {
	float range = 50.0f;
	float minDistance = FLT_MAX;
	uint64 closestUserId = 0;
	bool isFindTarget = false;
	float maxDistanceSquared = 1.0f * 1.0f;  // 원형 범위의 반지름의 제곱

	if (_userInfoList.empty() == false)
	{
		for (const auto& entry : _userInfoList) {
			float distance = IsPlayerInRanger(entry.second._pos, chara._pos);
			if (distance <= range && distance < minDistance) {
				minDistance = distance;
				closestUserId = entry.first;
				isFindTarget = true;
			}
		}
	}

	if ((isFindTarget) && (_userInfoList.find(closestUserId) != _userInfoList.end())) {
		return _userInfoList[closestUserId]._pos;
	}

	return chara._pos;
}