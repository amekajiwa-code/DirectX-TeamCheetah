#pragma once
#include "Session.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

	uint64 GetSessionId() { return _sessionId; }
	void SetSessionId(uint64 sessionId) { _sessionId = sessionId; }
private:
	uint64 _sessionId = 0;
};

