#include "pch.h"
#include "PlayerSoundController.h"

PlayerSoundController::PlayerSoundController()
{
	for (int i = 0; i < (int)PlayerAnimType::None; ++i) {
		shared_ptr<Sounds> sound = nullptr;
		soundContainer.push_back(make_pair((PlayerAnimType)i,sound));
	}
}

PlayerSoundController::~PlayerSoundController()
{
}

void PlayerSoundController::PlaySound(PlayerAnimType state)
{
	if (state != prevType) {
		for (auto c : soundContainer) {
			if (state == c.first) {
				if (c.second != nullptr) {
					c.second->Play3DEffect(&targetTransform->GetPositionRef());
					break;
				}
			}
		}
	}
	prevType = state;
}

void PlayerSoundController::SetSound(PlayerAnimType state, shared_ptr<Sounds > sound)
{
	for (int i = 0; i < (int)PlayerAnimType::None;++i) {
		if (state == soundContainer[i].first) {
			soundContainer[i].second = sound;
			break;
		}
	}
}
