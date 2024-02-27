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
		if (mob.second._isAlive == false) continue;

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
				// �÷��̾ ���ϴ� ���� ���� ���
				DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(it->second._pos, mob.second._pos);
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

				mob.second._Rotate = Vec3(0.0f, angle, 0.0f);
			}
			//State
			mob.second._targetPos = it->second._pos;

			if (distance <= 15.0f)
			{
				state = AIState::Attack;
			}
			else if (distance <= range)
			{
				state = AIState::Run;
			}
			else if (distance > range)
			{
				state = AIState::Stand;
			}

			Vec3 direction;

			switch (state)
			{
			case AIState::None:
				break;
			case AIState::Stand:
				mob.second._animState = EnemyUnitState::Stand;
				break;
			case AIState::Walk:
				break;
			case AIState::Run:
				mob.second._animState = EnemyUnitState::Run;
				direction = mob.second._targetPos - mob.second._pos;
				mob.second._pos += direction * TIMER().getDeltaTime();
				break;
			case AIState::Damaged:
				mob.second._animState = EnemyUnitState::Damaged;
				break;
			case AIState::Death:
				break;
			case AIState::Battle:
				break;
			case AIState::Attack:
				mob.second._animState = EnemyUnitState::Attack;
				GSessionManager.EnemyIsAttack(it->second, mob.second);
				break;
			case AIState::Ability1:
				break;
			case AIState::Ability2:
				break;
			case AIState::End:
				break;
			default:
				break;
			}
		}
	}

	return true;
}
