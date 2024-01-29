#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"


void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case PACKET_USER_INFO:
		Handle_USER_INFO(buffer, len);
		break;
	case PACKET_MONSTER_INFO:
		Handle_MONSTER_INFO(buffer, len);
		break;
	case PACKET_DISCONNECT:
		Handle_USER_DISCONNECT(buffer, len);
		break;
	default:
		break;
	}
}

void ClientPacketHandler::Handle_USER_INFO(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	Player_INFO userInfo;
	br >> userInfo;

	std::lock_guard<std::mutex> lock(_mutex);

	if (header.other == false)
	{
		_userInfo = userInfo;
		cout << "your uid : " << userInfo._uid << endl;
		cout << "position : ( " << userInfo._pos.x << ", " << userInfo._pos.y << ", " << userInfo._pos.z << " )" << endl;
	}
	else if (_userInfo._uid != userInfo._uid)
	{
		// uid�� �̹� otherUserInfoMap�� �ִ��� Ȯ��
		auto it = otherUserInfoMap.find(userInfo._uid);

		if (it != otherUserInfoMap.end()) {
			// �̹� �����ϴ� Ű�� �ش��ϴ� ���� ����
			it->second = userInfo;
		}
		else {
			// �������� �ʴ� ���, ���ο� ���� ����
			Player_INFO otherUserInfo = userInfo;
			otherUserInfo._isOnline = true;
			cout << "other uid : " << userInfo._uid << endl;
			cout << "other position : ( " << userInfo._pos.x << ", " << userInfo._pos.y << ", " << userInfo._pos.z << " )" << endl;
			otherUserInfoMap.insert(std::make_pair(userInfo._uid, otherUserInfo));
		}
	}
}

void ClientPacketHandler::Handle_MONSTER_INFO(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	MONSTER_INFO mobInfo;
	//br�� Ŀ���� ���� �����Ҷ����� ��� �̾Ƴ�
	while (br.ReadSize() < br.Size())
	{
		br >> mobInfo;

		auto it = _mobInfoList.find(mobInfo._instanceId);
		if (it != _mobInfoList.end())
		{
			it->second = mobInfo;
		}
		else
		{
			_mobInfoList.insert(make_pair(mobInfo._instanceId, mobInfo));
		}
	}
}

void ClientPacketHandler::Handle_USER_DISCONNECT(BYTE* buffer, int32 len)
{
	
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	uint64 uid;

	br >> uid;

	std::lock_guard<std::mutex> lock(_mutex);

	auto it = otherUserInfoMap.find(uid);

	if (it != otherUserInfoMap.end()) {
		it->second._isOnline = false;
	}
}
SendBufferRef ClientPacketHandler::Make_USER_INFO(Player_INFO userInfo)
{
	std::lock_guard<std::mutex> lock(_mutex);

	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << userInfo;

	header->size = bw.WriteSize();
	header->id = PACKET_USER_INFO;

	sendBuffer->Close(bw.WriteSize()); //����� ���̸�ŭ �ݾ���

	return sendBuffer;
}

SendBufferRef ClientPacketHandler::Make_MONSTER_INFO(MONSTER_INFO info)
{
	std::lock_guard<std::mutex> lock(_mutex);

	SendBufferRef sendBuffer = GSendBufferManager->Open(4096); //4kb
	BufferWriter bw(sendBuffer->Buffer(), sendBuffer->AllocSize());
	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << info;

	header->size = bw.WriteSize();
	header->id = PACKET_MONSTER_INFO;

	sendBuffer->Close(bw.WriteSize()); //����� ���̸�ŭ �ݾ���

	return sendBuffer;
}

