#pragma once
#include"pch.h"
#include "PlainHeightAdder.h"
class Terrain :public GameObject
{
	shared_ptr<Plain> plain=nullptr;
	shared_ptr<PlainHeightAdder> plainHeightAddr = nullptr;
	Terrain() {};

	float Lerp(float start, float end, float tangent)
	{
		return start - (start *tangent) + (end * tangent);
	}
public:
public:
	Terrain(HeightPlainInfo HeightDesc);
	virtual ~Terrain() {};
public:
	shared_ptr<Plain> GetPlain();
	float GetHeight(float posX,float posZ);
	//virtual void Awake() override;
	virtual void Start() override;
	//virtual void FixedUpdate() override;
	virtual void Update() override;
	//virtual void LateUpdate() override;

};

