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
	//VSync(수직동기화)
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
#define MAX_MODEL_INSTANCE 500

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

struct InstancedTweenDesc
{
	TweenDesc tweens[MAX_MODEL_INSTANCE];
};

struct JumpFlag
{
	bool isJumpUP = false;
	bool isJumpFall = false;
	bool isJumEnd = false;
	bool isJump = false;
};

//Event Protocol
struct EventArgs
{
	std::weak_ptr<GameObject> _sender;
	DWORD _protocol;
};

struct ShadowDesc {
	Matrix mat;
};

struct ShadowViewDesc {
	Matrix shadowView;
	Matrix shadowProj;
};

//Character Info...
struct CHARACTER_INFO
{
	//wstring _name;
	uint32 _maxHp = 1000;
	uint32 _maxMp = 1000;
	uint32 _hp = 1000;
	uint32 _mp = 1000;
	uint16 _atk = 100;
	//uint16 _def = 100;
	uint16 _moveSpeed = 10;
	uint16 _aggroLevel = 100;
	float _attackRange = 15.0f;
	Vec3 _pos = { 0.0f, 0.0f, 0.0f };
	Vec3 _Rotate = { 0.0f, 0.0f, 0.0f };
	bool _isAlive = true;
	bool _isAttack = false;
	bool _isBattle = false;
	double _timeStamp = 0.0f;
};

struct MESSAGE
{
	char _messageBox[50];
};

struct Player_INFO : public CHARACTER_INFO
{
	uint64 _uid;
	bool _isOnline = false;
	PlayerUnitState _animState = PlayerUnitState::Stand;
	JumpFlag _jumpFlag;
	MESSAGE _message;
};

struct MONSTER_INFO : public CHARACTER_INFO
{
	uint64 _instanceId = 0;
	Vec3 _targetPos = { 0.f, 0.f, 0.f };
	bool _isMove = false;
	EnemyUnitState _animState = EnemyUnitState::Stand;
};