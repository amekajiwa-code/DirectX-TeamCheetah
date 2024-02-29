#include "pch.h"
#include "EnemySoundController.h"


EnemySoundController::EnemySoundController()
{
	for (int i = 0; i < (int)EnemyAnimType::None; ++i) {
		shared_ptr<Sounds> sound = nullptr;
		soundContainer.push_back(make_pair((EnemyAnimType)i, sound));
	}
}

EnemySoundController::~EnemySoundController()
{
}

void EnemySoundController::PlaySound(EnemyAnimType state)
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

void EnemySoundController::SetSound(EnemyAnimType state, shared_ptr<Sounds > sound)
{
	for (int i = 0; i < (int)EnemyAnimType::None; ++i) {
		if (state == soundContainer[i].first) {
			soundContainer[i].second = sound;
			break;
		}
	}
}
