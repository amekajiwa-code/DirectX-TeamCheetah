#pragma once

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	~PlayerController();
private:
	weak_ptr<ModelAnimator> _animator;
private:

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

