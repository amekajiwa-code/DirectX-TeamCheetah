#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "Types.h"

class GameObject;

struct CGameDesc
{
	//Sample or Root Game Scene Pointer
	std::shared_ptr<class IExecute> App = nullptr;
	//Program Name
	std::wstring AppName = L"Default";
	//Win Size
	float width = 800.f;
	float height = 600.f;
	//WIN API
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	bool windowed = true;
	//VSync(��������ȭ)
	bool vsync = false;
	//BackBuffer Clear Color
	Color clearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	//MouseWheel if (state == 1) up, or (state == -1 )down
	int WheelState = 0;
};

struct GlobalDesc
{
	Matrix V = Matrix::Identity;
	Matrix P = Matrix::Identity;
	Matrix VP = Matrix::Identity;
	Matrix VInv = Matrix::Identity;
};

struct TransformDesc
{
	Matrix W = Matrix::Identity;
};

// Light
struct LightDesc
{
	Color ambient = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	Vec3 direction;
	float padding0 = 0;
};

//Material
struct MaterialDesc
{
	Color ambient = Color(0.f, 0.f, 0.f, 1.f);
	Color diffuse = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(0.f, 0.f, 0.f, 1.f);
	Color emissive = Color(0.f, 0.f, 0.f, 1.f);
};

//Bone
#define MAX_MODEL_TRANSFORMS 250	
#define MAX_MODEL_KEYFRAMES 250

struct BoneDesc
{
	Matrix transforms[MAX_MODEL_TRANSFORMS];
};

//Animation
struct AnimTransform
{
	using TransformArrayType = std::array<Matrix, MAX_MODEL_TRANSFORMS>;
public:
	std::array<TransformArrayType, MAX_MODEL_KEYFRAMES> transforms;
};

struct KeyframeDesc
{
	int32 animIndex = 0;
	uint32 currentFrame = 0;
	uint32 nextFrame = 0;

	float ratio = 0.f;
	float sumTime = 0.f;
	float speed = 1.f;
	Vec2 padding;
};

struct TweenDesc
{
	TweenDesc()
	{
		current.animIndex = -1;
		next.animIndex = -1;
	}
	void ClearCurrentAnim()
	{
		current.animIndex = -1;
		current.currentFrame = 0;
		current.nextFrame = 0;
		current.sumTime = 0;
		current.ratio = 0;
		tweenRatio = 0;
		tweenSumTime = 0;
	}
	void ClearNextAnim()
	{
		next.animIndex = -1;
		next.currentFrame = 0;
		next.nextFrame = 0;
		next.sumTime = 0;
		next.ratio = 0;
		tweenRatio = 0;
		tweenSumTime = 0;
	}
	float tweenDuration = 1.0f;
	float tweenRatio = 1.0f;
	float tweenSumTime = 1.0f;
	float padding = 0.f;
	KeyframeDesc current;
	KeyframeDesc next;
};

//Event Protocol
struct EventArgs
{
	std::weak_ptr<GameObject> _sender;
	DWORD _protocol;
};
