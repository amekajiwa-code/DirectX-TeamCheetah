#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	//������ �ڵ忡�� ������ �ϰ�����
	/*���ʷ� ������ �������� OnConnected���� Send�� �ϰ�
	�������� OnRecv�� �ѵ� ���ڷ�*/
	virtual void OnConnected() override
	{
		cout << "Connected To Server!" << endl;
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		ClientPacketHandler::Instance().HandlePacket(buffer, len);
	}

	virtual void OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		//cout << "Disconnected..." << endl;
	}
};