#pragma once
#include "Component.h"
#include "Animation.h"

class Animator : public Component
{
	using Super = Component;
public:
	Animator();
	virtual ~Animator();
private:
	double _sumTime = 0.0;
	int32 _currentFrameIndex = 0;
	shared_ptr<Animation> _currentAnimation;
public:
	shared_ptr<Animation> GetCurrentAnimation();
	const Keyframe& GetCurrentKeyframe();
public:
	void SetAnimation(shared_ptr<Animation> animation) { _currentAnimation = animation; }
public:
	void Init();
	virtual void Update() override;
};

