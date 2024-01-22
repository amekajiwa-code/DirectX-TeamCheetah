#pragma once
#include <windows.h>
#include "DirectXMath.h"
#include "SimpleMath.h"

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

//DX
using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Color = DirectX::XMFLOAT4;

using Matrix = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

//Cameratype
enum class CameraType
{
	None,
	Debug,
	Normal,
	Target,
	End
};

//Model Type
enum class ModelType
{
	None,
	Skeletal,
	Static,
	Effect,
	End
};

//AssetType
enum class AssetType
{
	None,
	SkeletalMesh,
	StaticMesh,
	Effect,
	Animation,
	End
};

//Object Type
enum class ObjectType
{
	None,
	Unit,
	Environment,
	Structure,
	Ui,
	End
};

//Unit State
enum class PlayerUnitState
{
	None,
	Stand,
	FrontMove,
	FrontRightMove,
	FrontLeftMove,
	BackMove,
	BackRightMove,
	BackLeftMove,
	RightMove,
	LeftMove,
	Jump,
	Stun,
	Loot,
	Death,
	Battle,
	Attack,
	Ability,
	End
};

enum class PlayerAnimType
{
	Stand,
	FrontWalk,
	BackWalk,
	FrontRun,
	BackRun,
	JumpStart,
	JumpFall,
	JumpEnd,
	JumpEndRun,
	Stun,
	Loot,
	Death,
	Battle,
	Attack1,
	Attack2,
	Casting,
	Ability1,
	Ability2,
	None
};