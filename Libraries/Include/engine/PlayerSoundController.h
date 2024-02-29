#pragma once
#include "PlayerAnimState.h"
class Transform;

class PlayerSoundController : public MonoBehaviour
{
	
private:
	shared_ptr<Transform> targetTransform;
	PlayerAnimType prevType=PlayerAnimType::None;
	vector<pair<PlayerAnimType, shared_ptr<Sounds>>> soundContainer;
public:
	void Set(shared_ptr<Transform> transform) {
		targetTransform = transform;
	}
	PlayerSoundController();
	~PlayerSoundController();
	void PlaySound(PlayerAnimType state);
	void SetSound(PlayerAnimType state, shared_ptr<Sounds > sound);
};

