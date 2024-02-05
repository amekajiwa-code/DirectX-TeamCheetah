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
		// �÷��̾ ���ϴ� ���� ���� ���
		DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(playerPos, DirectX::XMLoadFloat3(&pair.second._targetPos));
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
