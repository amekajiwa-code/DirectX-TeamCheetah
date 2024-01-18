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

	//콘텐츠 코드에서 재정의 하고있음
	/*최초로 연결이 되있을떄 OnConnected에서 Send를 하고
	서버에서 OnRecv를 한뒤 에코로*/
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