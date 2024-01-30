#pragma once


class AIController : public MonoBehaviour, public enable_shared_from_this<AIController>
{
public:
	AIController(){}
	virtual ~AIController(){}
private:
	weak_ptr<Transform>		_transform;
	Vec3 _targetPos;
private:
	weak_ptr<ModelAnimator> _animator;
public:

public:
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

