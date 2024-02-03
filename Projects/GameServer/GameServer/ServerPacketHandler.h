#pragma once
#include <map>
#include <DirectXMath.h>
#include "Timer.h"

enum
{
	PACKET_CONNECT = 1,
	PACKET_USER_INFO = 2,
	PACKET_MONSTER_INFO = 3,
	PACKET_DISCONNECT = 99,
};

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

struct JumpFlag
{
	bool isJumpUP = false;
	bool isJumpFall = false;
	bool isJumEnd = false;
	bool isJump = false;
};

struct CHARACTER_INFO
{
	//wstring _name;
	//uint32 _hp;
	//uint16 _atk;
	uint16 _moveSpeed = 10.0f;
	//float _attackRange;
	uint16 _aggroLevel = 100;
	DirectX::XMFLOAT3 _pos = { 0.f, 0.f, 0.f };
	DirectX::XMFLOAT3 _Rotate = { 0.f, 0.f, 0.f };
	bool _isAlive = true;
	double _timeStamp = 0.0f;
};

struct Player_INFO : public CHARACTER_INFO
{
	uint64 _uid = 0;
	bool _isOnline;
	PlayerUnitState _animState = PlayerUnitState::Stand;
	JumpFlag _jumpFlag;
};

struct MONSTER_INFO : public CHARACTER_INFO
{
	uint64 _instanceId = 0;
	DirectX::XMFLOAT3 _targetPos = { 0.f, 0.f, 0.f };
	bool _isMove = false;
	EnemyUnitState _animState = EnemyUnitState::Stand;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);
	static void Handle_USER_INFO(BYTE* buffer, int32 len);
	static void Handle_MONSTER_INFO(BYTE* buffer, int32 len);

	static SendBufferRef Make_USER_CONNECT();
	static SendBufferRef Make_USER_INFO(Player_INFO userInfo, bool otherPacket);
	static SendBufferRef Make_MONSTER_INFO(map<uint64, MONSTER_INFO> mobInfo);
	static SendBufferRef Make_USER_DISCONNECT(uint64 uid);
}; 
