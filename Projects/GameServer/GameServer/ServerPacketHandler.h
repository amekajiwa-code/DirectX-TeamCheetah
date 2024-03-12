#pragma once
#include <map>
#include <DirectXMath.h>
#include "Timer.h"

enum
{
	PACKET_CONNECT = 1,
	PACKET_USER_INFO = 2,
	PACKET_MONSTER_INFO = 3,
	PACKET_MESSAGE = 4,
	PACKET_BATTLE = 5,
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

enum class MapType
{
	None,
	Lobby,
	Dungeon,
	BossRoom
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
	uint32 _instanceId = 0;
	MapType _spawnMapType = MapType::Lobby;
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
	uint32 _uid = 0;
	bool _isOnline = false;
	PlayerUnitState _animState = PlayerUnitState::Stand;
	JumpFlag _jumpFlag;
};

struct MONSTER_INFO : public CHARACTER_INFO
{
	uint32 _monsterId = 0;
	Vec3 _targetPos = { 0.f, 0.f, 0.f };
	bool _isMove = false;
	EnemyUnitState _animState = EnemyUnitState::Stand;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);
	static void Handle_USER_INFO(BYTE* buffer, int32 len);
	static void Handle_MONSTER_INFO(BYTE* buffer, int32 len);
	static void Handle_MESSAGE(BYTE* buffer, int32 len);
	static void Handle_BATTLE(BYTE* buffer, int32 len);

	static SendBufferRef Make_USER_CONNECT();
	static SendBufferRef Make_USER_INFO(Player_INFO userInfo, bool otherPacket);
	static SendBufferRef Make_MONSTER_INFO(map<uint64, MONSTER_INFO> mobInfo);
	static SendBufferRef Make_USER_DISCONNECT(uint64 uid);
	static SendBufferRef Make_MESSAGE(MESSAGE message);
};
