#pragma once
class UiObject : public MonoBehaviour
{
public:
	UiObject();
	virtual ~UiObject();
public:
	virtual void Update() override;
};

