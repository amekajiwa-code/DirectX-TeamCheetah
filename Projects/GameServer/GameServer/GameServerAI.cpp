#include "pch.h"
#include "GameServerAI.h"
#include "GameSessionManager.h"
#include "Timer.h"

float IsPlayerInRanger(const Vec3& playerPos, const Vec3& monsterPos)
{
	Vec3 diff = DirectX::XMVectorSubtract(playerPos, monsterPos);
	float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(diff));

	return distance;
}

float CalculateAngle(const Vec3& v1, const Vec3& v2) {
	return DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(v1, v2)));
}

void GameServerAI::Update()
{
	CalcNextBehavior();
}

bool GameServerAI::CalcNextBehavior()
{
	for (auto& mob : GSessionManager.GetMobInfoList())
	{
		float minDistance = FLT_MAX;
		uint64 closestUserId = 0;

		for (const auto& user : GSessionManager.GetUserInfoList())
		{
			float distance = IsPlayerInRanger(user.second._pos, mob.second._pos);
			if (distance <= range && distance < minDistance) {
				minDistance = distance;
				closestUserId = user.first;
			}
		}

		const auto it = GSessionManager.GetUserInfoList().find(closestUserId);

		if (it != GSessionManager.GetUserInfoList().end())
		{
			float distance = IsPlayerInRanger(mob.second._pos, it->second._pos);
			//Rotate
			if (distance <= range)
			{
				// 플레이어를 향하는 방향 벡터 계산
				DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(it->second._pos, mob.second._pos);
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

				mob.second._Rotate = Vec3(0.0f, angle, 0.0f);
			}
			//Move
			mob.second._targetPos = it->second._pos;

			if (distance <= 20.0f)
			{
				mob.second._animState = EnemyUnitState::Attack;
			}
			else if (distance <= range)
			{
				Vec3 direction = mob.second._targetPos - mob.second._pos;
				mob.second._pos += direction * TIMER().getDeltaTime();
				mob.second._animState = EnemyUnitState::Run;
			}
			else
			{
				mob.second._animState = EnemyUnitState::Stand;
			}
		}
	}

	for (auto mob : GSessionManager.GetMobInfoList())
	{
		switch (mob.second._animState)
		{
		case EnemyUnitState::None:
			break;
		case EnemyUnitState::Stand:
			break;
		case EnemyUnitState::Walk:
			break;
		case EnemyUnitState::Run:
			break;
		case EnemyUnitState::Damaged:
			break;
		case EnemyUnitState::Death:
			break;
		case EnemyUnitState::Battle:
			break;
		case EnemyUnitState::Attack:
			break;
		case EnemyUnitState::Ability1:
			break;
		case EnemyUnitState::Ability2:
			break;
		case EnemyUnitState::End:
			break;
		default:
			break;
		}
	}

	return true;
}