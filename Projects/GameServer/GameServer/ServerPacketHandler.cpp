#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "GameSession.h"
#include "GameSessionManager.h"

void ServerPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case PACKET_USER_INFO:
		Handle_USER_INFO(buffer, len);
		break;
	case PACKET_MONSTER_INFO:
		Handle_MONSTER_INFO(buffer, len);
		break;
	case PACKET_MESSAGE:
		Handle_MESSAGE(buffer, len);
		break;
	case PACKET_BATTLE:
		Handle_BATTLE(buffer, len);
		break;
	default:
		break;
	}
}

void ServerPacketHandler::Handle_USER_INFO(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	Player_INFO userInfo;
	br >> userInfo;
	userInfo._timeStamp = TIMER().getCurrentTime();

	/*cout << "uid : " << userInfo._uid << endl;
	cout << "position : (" << userInfo._pos.x << ", " << userInfo._pos.y << ", " << userInfo._pos.z << ")" << endl;
	cout << "hp : " << userInfo._hp << endl;*/

	SendBufferRef sendBuffer = ServerPacketHandler::Make_USER_INFO(userInfo, true);
	GSessionManager.UpdateUserInfo(userInfo);
	GSessionManager.Broadcast(sendBuffer);
}

void ServerPacketHandler::Handle_MONSTER_INFO(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	MONSTER_INFO info;
	br >> info;

	GSessionManager.UpdateMobInfo(info);
}

void ServerPacketHandler::Handle_MESSAGE(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	MESSAGE message;
	br >> message;

	SendBufferRef sendBuffer = ServerPacketHandler::Make_MESSAGE(message);
	GSessionManager.Broadcast(sendBuffer);
}

void ServerPacketHandler::Handle_BATTLE(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	Player_INFO atkInfo;
	uint32 tgtId;
	br >> atkInfo >> tgtId;

	auto it = GSessionManager.GetMobInfoList().find(tgtId);
	if (it != GSessionManager.GetMobInfoList().end())
	{
		if (atkInfo._atk >= it->second._hp) //막타
		{
			it->second._hp = 0;
			it->second._isAlive = false;
		}
		else
		{
			it->second._hp -= atkInfo._atk;
		}


		
		GSessionManager.UpdateMobInfo(it->second);
	}

	
}

SendBufferRef ServerPacketHandler::Make_USER_CONNECT()
{
	//TODO: 플레이어 정보, 초기정보
	return nullptr;
}

SendBufferRef ServerPacketHandler::Make_USER_INFO(Player_INFO userInfo, bool otherPacket)
{
	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << userInfo;

	header->size = bw.WriteSize();
	header->id = PACKET_USER_INFO;
	header->other = otherPacket;

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌

	return sendBuffer;
}

SendBufferRef ServerPacketHandler::Make_MONSTER_INFO(map<uint64, MONSTER_INFO> charaInfo)
{
	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	for (const auto& pair : charaInfo) {
		uint64 id = pair.first;
		MONSTER_INFO info = pair.second;
		info._timeStamp = TIMER().getCurrentTime();

		cout << "map id : " << pair.second._spawnMapId << endl;
		cout << "position : ( " << pair.second._pos.x << ", " << pair.second._pos.y << ", " << pair.second._pos.z << " )" << endl;

		bw << info;
	}

	header->size = bw.WriteSize();
	header->id = PACKET_MONSTER_INFO;

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌

	return sendBuffer;
}

SendBufferRef ServerPacketHandler::Make_MESSAGE(MESSAGE message)
{
	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << message;

	header->size = bw.WriteSize();
	header->id = PACKET_MESSAGE;

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌

	return sendBuffer;
}

SendBufferRef ServerPacketHandler::Make_USER_DISCONNECT(uint64 uid)
{
	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << uid;

	header->size = bw.WriteSize();
	header->id = PACKET_DISCONNECT;
	header->other = true;

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌
	return sendBuffer;
}