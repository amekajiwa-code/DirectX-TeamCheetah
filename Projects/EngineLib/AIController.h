#pragma once


class AIController : public MonoBehaviour, public enable_shared_from_this<AIController>
{
public:
	AIController(){}
	virtual ~AIController(){}
private:

public:

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

