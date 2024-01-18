#pragma once
#include <map>
#include <DirectXMath.h>

enum
{
	HANDLE_CONNECT = 1,
	HANDLE_INFO = 2,
	HANDLE_CHARA_INFO = 3,
	HANDLE_DISCONNECT = 99,
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
	DirectX::XMFLOAT3 _pos;
	DirectX::XMFLOAT3 _nextPos;
	bool _isAlive = true;
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
