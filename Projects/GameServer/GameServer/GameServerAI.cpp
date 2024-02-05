#include "pch.h"
#include "GameServerAI.h"

#include "GameSessionManager.h"

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
	// 부동 소수점 비교를 위해 허용 가능한 오차 범위를 지정
	auto floatEquals = [tolerance](float a, float b) {
		return std::fabs(a - b) < tolerance;
		};

	// x, y, z 중에서 tolerance 이라도 차이가 나면 true를 반환
	if (!floatEquals(v1.m128_f32[0], v2.m128_f32[0]) || !floatEquals(v1.m128_f32[1], v2.m128_f32[1]) || !floatEquals(v1.m128_f32[2], v2.m128_f32[2])) {
		return true;
	}

	// 모든 차이가 허용 가능한 오차 범위 내에 있으면 false 반환
	return false;
}

void GameServerAI::Start()
{
	CalcNextBehavior();
}

bool GameServerAI::MoveAI(DirectX::XMFLOAT3 targetPos)
{
	for (auto& pair : GSessionManager.GetMobInfoList())
	{
		pair.second._pos = targetPos;
		pair.second._targetPos = targetPos;
		pair.second._animState = EnemyUnitState::Run;
	}

	return false;
}

bool GameServerAI::RotateAI(DirectX::XMFLOAT3 targetPos)
{
	DirectX::XMVECTOR playerPos = DirectX::XMLoadFloat3(&targetPos);

	for (auto& pair : GSessionManager.GetMobInfoList())
	{
		// 플레이어를 향하는 방향 벡터 계산
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(playerPos, DirectX::XMLoadFloat3(&pair.second._targetPos));
		direction = DirectX::XMVector3Normalize(direction);

		// 전방 벡터와 방향 벡터 사이의 각도 계산
		DirectX::XMVECTOR forwardVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // 몬스터가 양의 z축 방향을 향한다고 가정

		// 플레이어가 몬스터의 위치를 기준으로 어느 방향에 있는지 각도 계산
		float angle = atan2(DirectX::XMVectorGetX(direction), DirectX::XMVectorGetZ(direction));

		// 플레이어가 몬스터의 왼쪽에 있는지 오른쪽에 있는지 결정
		float crossProduct = DirectX::XMVectorGetY(DirectX::XMVector2Cross(forwardVector, direction));
		if (crossProduct < 0.0f) {
			angle = -angle; // 플레이어가 몬스터의 왼쪽에 있으므로 시계 방향으로 회전
		}

		pair.second._Rotate = DirectX::XMFLOAT3(0.0f, angle, 0.0f);
	}

	return false;
}

bool GameServerAI::CalcNextBehavior()
{
	for (const auto& pair : GSessionManager.GetUserInfoList())
	{
		MoveAI(pair.second._pos);
		RotateAI(pair.second._pos);
	}

	return true;
}
