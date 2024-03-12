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
using Ray = DirectX::SimpleMath::Ray;

using InstanceID = std::pair<uint64, uint64>;

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
	PlayableUnit,
	EnemyUnit,
	Environment,
	Structure,
	Ui,
	End
};

enum class AIType
{
	None,
	PlayableUnit,
	EnemyUnit,
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
	Damaged,
	Death,
	Battle,
	Attack,
	Ability1,
	Ability2,
	End
};

enum class EnemyUnitState
{
	None,
	Stand,
	Walk,
	Run,
	Damaged,
	Death,
	Battle,
	Attack,
	Ability1,
	Ability2,
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
	Stun,
	Loot,
	Damaged,
	Death,
	Battle,
	Attack1,
	Attack2,
	Casting,
	Ability1,
	Ability2,
	None
};

enum class EnemyAnimType
{
	Stand,
	Walk,
	Run,
	Damaged,
	Death,
	Battle,
	Attack1,
	Attack2,
	Casting,
	Ability1,
	Ability2,
	None
};

//Collision Type
enum class ColliderType
{
	AABB,
	OBB,
	Sphere
};

//Item Type
enum class ItemType : uint8
{
	None,
	Helm,
	LeftShoulder,
	RightShoulder,
	Belt,
	Weapon,
	Shield,
	Consumable,
	End
};

enum class UsableItemType : uint8
{
	None,
	ALL,
	Warrior,
	Mage,
	Priest,
	End
};

//Map Type
enum class MapType
{
	None,
	Lobby,
	Dungeon,
	BossRoom
};

//Skill Type
enum class SkillType
{
	NormalAttack,
	WhirlWind,
	IceArrow,
	Blizzard,
	Test_AllAttack,
};
