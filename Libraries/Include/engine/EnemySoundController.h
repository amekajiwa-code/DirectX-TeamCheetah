#pragma once
#include "EnemyAnimState.h"
class Transform;

class EnemySoundController : public MonoBehaviour
{

private:
	shared_ptr<Transform> targetTransform;
	EnemyAnimType prevType = EnemyAnimType::None;
	vector<pair<EnemyAnimType, shared_ptr<Sounds>>> soundContainer;
public:
	void Set(shared_ptr<Transform> transform) {
		targetTransform = transform;
	}
	EnemySoundController();
	~EnemySoundController();
	void PlaySound(EnemyAnimType state);
	void SetSound(EnemyAnimType state, shared_ptr<Sounds > sound);
};

