#include "pch.h"
#include "Animator.h"

Animator::Animator() : Super(ComponentType::Animator)
{
}

Animator::~Animator() 
{
}

shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const Keyframe& Animator::GetCurrentKeyframe()
{
	return _currentAnimation->GeyKeyframe(_currentFrameIndex);
}

void Animator::Init()
{
}

void Animator::Update()
{
	shared_ptr<Animation> anim = GetCurrentAnimation();
	if (anim == nullptr)
		return;

	const Keyframe& keyframe = anim->GeyKeyframe(_currentFrameIndex);

	double deltaTime = MANAGER_TIME()->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= keyframe.time)
	{
		_currentFrameIndex++;
		int32 totalCount = anim->GetKeyframeCount();

		if (_currentFrameIndex >= totalCount)
		{
			if (anim->IsLoop())
			{
				_currentFrameIndex = 0;
			}
			else
			{
				_currentFrameIndex = totalCount - 1;
			}
		}
		_sumTime = 0.0;
	}

}
