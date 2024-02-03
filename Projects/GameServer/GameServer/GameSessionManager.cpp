#include "pch.h"
#include "GameSessionManager.h"

GameSessionManager GSessionManager;
bool isUpdate = true;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	//�� ���� ���
	Player_INFO userInfo; 
	userInfo._uid = sessionIdCount; //session�� ������ id send
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
	// ���� ���� ������ ����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(-100.0f, 100.0f);

	for (int id = 0; id < 1; ++id)
	{
		MONSTER_INFO c0;

		// ������ ���� ������ x �� z�� ���� ������ �� ����
		c0._instanceId = id;
		c0._pos = { distribution(gen), 0.0f, distribution(gen) };
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

float IsPlayerInRanger(const DirectX::XMFLOAT3& playerPos, const DirectX::XMFLOAT3& monsterPos)
{
	DirectX::XMVECTOR playerVec = DirectX::XMLoadFloat3(&playerPos);
	DirectX::XMVECTOR monsterVec = DirectX::XMLoadFloat3(&monsterPos);

	DirectX::XMVECTOR diff = DirectX::XMVectorSubtract(playerVec, monsterVec);
	float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(diff));

	return distance;
}

float CalculateAngle(const DirectX::XMVECTOR& v1, const DirectX::XMVECTOR& v2) {
	return DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(v1, v2)));
}

bool HasDifference(const DirectX::XMVECTOR& v1, const  DirectX::XMVECTOR& v2, float tolerance = 0.0001f) {
	// �ε� �Ҽ��� �񱳸� ���� ��� ������ ���� ������ ����
	auto floatEquals = [tolerance](float a, float b) {
		return std::fabs(a - b) < tolerance;
		};

	// x, y, z �߿��� tolerance �̶� ���̰� ���� true�� ��ȯ
	if (!floatEquals(v1.m128_f32[0], v2.m128_f32[0]) || !floatEquals(v1.m128_f32[1], v2.m128_f32[1]) || !floatEquals(v1.m128_f32[2], v2.m128_f32[2])) {
		return true;
	}

	// ��� ���̰� ��� ������ ���� ���� ���� ������ false ��ȯ
	return false;
}

//TODO: �����ȿ� �ִ³��� ���� ������ Ÿ������ ���
void GameSessionManager::CalcNextPos(MONSTER_INFO* chara) {
	float range = 30.0f;
	float minDistance = FLT_MAX;
	uint64 closestUserId = 0;
	bool isFindTarget = false;
	float maxDistanceSquared = 1.0f * 1.0f;  // ���� ������ �������� ����

	if (_userInfoList.empty() == false)
	{
		for (const auto& entry : _userInfoList) {
			float distance = IsPlayerInRanger(entry.second._pos, chara->_pos);
			if (distance <= 10.0f)
			{
				chara->_isMove = false;
				chara->_animState = EnemyUnitState::Attack;
				//������ ����
			}
			else if (10.0f <= distance <= range ) {
				minDistance = distance;
				closestUserId = entry.first;
				isFindTarget = true;
				chara->_isMove = true;
			}
			else
			{
				
			}
		}
	}


	if ((isFindTarget) && (_userInfoList.find(closestUserId) != _userInfoList.end())) {
		DirectX::XMVECTOR playerPos = DirectX::XMLoadFloat3(&_userInfoList[closestUserId]._pos);
		DirectX::XMVECTOR monsterPos = DirectX::XMLoadFloat3(&chara->_pos);

		// �÷��̾ ���ϴ� ���� ���� ���
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(playerPos, monsterPos);
		direction = DirectX::XMVector3Normalize(direction);

		// ���� ���Ϳ� ���� ���� ������ ���� ���
		DirectX::XMVECTOR forwardVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // ���Ͱ� ���� z�� ������ ���Ѵٰ� ����

		// �÷��̾ ������ ��ġ�� �������� ��� ���⿡ �ִ��� ���� ���
		float angle = atan2(DirectX::XMVectorGetX(direction), DirectX::XMVectorGetZ(direction));

		// �÷��̾ ������ ���ʿ� �ִ��� �����ʿ� �ִ��� ����
		float crossProduct = DirectX::XMVectorGetY(DirectX::XMVector2Cross(forwardVector, direction));
		if (crossProduct < 0.0f) {
			angle = -angle; // �÷��̾ ������ ���ʿ� �����Ƿ� �ð� �������� ȸ��
		}

		if (chara->_isMove)
		{
			chara->_targetPos = _userInfoList[closestUserId]._pos;
			chara->_pos = chara->_targetPos;
			chara->_Rotate = DirectX::XMFLOAT3(0.0f, angle, 0.0f);
			//chara->_animState = EnemyUnitState::Run;
		}
		else
		{
			chara->_animState = EnemyUnitState::Stand;
		}
	}

}