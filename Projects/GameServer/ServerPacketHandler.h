#pragma once
#include <map>
#include <DirectXMath.h>
#include "Timer.h"

enum
{
	HANDLE_CONNECT = 1,
	HANDLE_INFO = 2,
	HANDLE_CHARA_INFO = 3,
	HANDLE_DISCONNECT = 99,
};

enum class PlayerAnimState
{
	None,
	Idle,
	FrontWalk,
	BackWalk,
	Run,
	BackRun,
	Stun,
	Loot,
	Death,
	JumpStart,
	JumpFall,
	JumpEnd,
	Battle,
	Attack1,
	Attack2,
	Casting,
	Ability1,
	Ability2,
	End
};

struct CHARACTER_INFO
{
	uint64 _instanceId;
	//wstring _name;
	//uint32 _hp;
	//uint16 _atk;
	uint16 _moveSpeed = 10.0f;
	//uint16 _attackSpeed;
	//uint16 _attackRange;
	uint16 _aggroLevel = 100;
	DirectX::XMFLOAT3 _pos = { 0.f, 0.f, 0.f };
	DirectX::XMFLOAT3 _nextPos = {0.f, 0.f, 0.f};
	DirectX::XMFLOAT3 _Rotate = { 0.f, 0.f, 0.f };
	PlayerAnimState _animState = PlayerAnimState::Idle;
	bool _isAlive = true;
	double _timeStamp = 0.0f;
};

struct Player_INFO : public CHARACTER_INFO
{
	uint64 _uid;
	bool _isOnline;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);
	static void Handle_USER_INFO(BYTE* buffer, int32 len);
	static void Handle_CHARACTER_INFO(BYTE* buffer, int32 len);

	static SendBufferRef Make_USER_CONNECT();
	static SendBufferRef Make_USER_INFO(Player_INFO userInfo, bool otherPacket);
	static SendBufferRef Make_CHARACTER_INFO(map<uint64, CHARACTER_INFO> charaInfo);
	static SendBufferRef Make_USER_DISCONNECT(uint64 uid);
}; 