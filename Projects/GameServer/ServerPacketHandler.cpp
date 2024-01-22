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
	case HANDLE_INFO:
		Handle_USER_INFO(buffer, len);
		break;
	case HANDLE_CHARA_INFO:
		Handle_CHARACTER_INFO(buffer, len);
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

	cout << "uid : " << userInfo._uid << endl;
	cout << "position : (" << userInfo._pos.x << ", " << userInfo._pos.y << ", " << userInfo._pos.z << ")" << endl;

	SendBufferRef sendBuffer = ServerPacketHandler::Make_USER_INFO(userInfo, true);
	GSessionManager.UpdateUserInfo(userInfo);
	GSessionManager.Broadcast(sendBuffer);
}

void ServerPacketHandler::Handle_CHARACTER_INFO(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	CHARACTER_INFO info;
	br >> info;

	GSessionManager.UpdateCharaInfo(info);
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
	header->id = HANDLE_INFO;
	header->other = otherPacket;
	//header->timeStamp = TIMER().getCurrentTime();

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌

	return sendBuffer;
}

SendBufferRef ServerPacketHandler::Make_CHARACTER_INFO(map<uint64, CHARACTER_INFO> charaInfo)
{
	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	for (const auto& pair : charaInfo) {
		uint64 id = pair.first;
		CHARACTER_INFO info = pair.second;

		bw << info;
	}

	header->size = bw.WriteSize();
	header->id = HANDLE_CHARA_INFO;
	//header->timeStamp = TIMER().getCurrentTime();

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
	header->id = HANDLE_DISCONNECT;
	header->other = true;

	sendBuffer->Close(bw.WriteSize()); //사용한 길이만큼 닫아줌

	return sendBuffer;
}