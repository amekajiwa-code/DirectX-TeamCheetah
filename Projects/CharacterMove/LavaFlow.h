#pragma once

class Lava : public MonoBehaviour
{
private:
	//FLOW ASSET
	float maxDistance;
	float currentDistance = 0;
	float speed;
	bool reverse =false;
	bool enableHeight = false;
private:
	Lava() {};
public: 
	Lava(float maxDistance, float speed, bool enable_Height = false):maxDistance(maxDistance),speed(speed),enableHeight(enable_Height) {};
public:
	virtual void Update() override;

};

