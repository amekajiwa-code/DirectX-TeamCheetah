#include "pch.h"
#include "GameServerAI.h"
#include "GameSessionManager.h"
#include "Timer.h"

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

DirectX::XMVECTOR interpolate(double alpha, DirectX::XMVECTOR targetPos, DirectX::XMVECTOR prePos = DirectX::XMVECTOR{ 0.0f, 0.0f, 0.0f }) {
	// 선형 보간을 통한 실제 위치 계산
	float interpolatedX = (1.0 - alpha) * prePos.m128_f32[0] + alpha * targetPos.m128_f32[0];
	float interpolatedY = (1.0 - alpha) * prePos.m128_f32[1] + alpha * targetPos.m128_f32[1];
	float interpolatedZ = (1.0 - alpha) * prePos.m128_f32[2] + alpha * targetPos.m128_f32[2];

	return DirectX::XMVECTOR{ interpolatedX, interpolatedY, interpolatedZ };
}

void GameServerAI::Start()
{
	CalcNextBehavior();
}

bool GameServerAI::CalcNextBehavior()
{
	for (const auto& pair : GSessionManager.GetUserInfoList())
	{
		RotateAI(pair.second._pos);
		MoveAI(pair.second._pos);
	}

	return true;
}

bool GameServerAI::MoveAI(DirectX::XMFLOAT3 targetPos)
{
	for (auto& pair : GSessionManager.GetMobInfoList())
	{
		auto calcTime = std::chrono::high_resolution_clock::now() - std::chrono::seconds(static_cast<int>(pair.second._timeStamp));
		auto durationSec = std::chrono::duration_cast<std::chrono::duration<double>>(calcTime.time_since_epoch()).count();
		double alpha = fmin(1.0, durationSec / 1.0);

		pair.second._targetPos = targetPos;
		DirectX::XMVECTOR direction = XMLoadFloat3(&pair.second._targetPos) - XMLoadFloat3(&pair.second._pos);
		pair.second._pos += interpolate(alpha, direction) * pair.second._moveSpeed* Timer::getInstance().getDeltaTime();
		pair.second._animState = EnemyUnitState::Run;
	}

	return false;
}

bool GameServerAI::RotateAI(DirectX::XMFLOAT3 targetPos)
{
	DirectX::XMVECTOR playerPos = DirectX::XMLoadFloat3(&targetPos);

	for (auto& pair : GSessionManager.GetMobInfoList())
	{
		float distance = IsPlayerInRanger(pair.second._pos, targetPos);
		if (distance <= 10.0f)
		{
			break;
		}

		// 플레이어를 향하는 방향 벡터 계산
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(playerPos, DirectX::XMLoadFloat3(&pair.second._pos));
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