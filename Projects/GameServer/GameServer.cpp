#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"

int main()
{
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	} 

	GSessionManager.GenerateMobList();

	while (true)
	{
		for (auto pair : GSessionManager.GetMobInfoList()) {
			GSessionManager.CalcNextPos(&pair.second);
			GSessionManager.UpdateMobInfo(pair.second);
			cout << "pos: " << pair.second._pos.x << ", " << pair.second._pos.y << ", " << pair.second._pos.z << endl;
		}

		SendBufferRef sendBuffer = ServerPacketHandler::Make_MONSTER_INFO(GSessionManager.GetMobInfoList());
		GSessionManager.Broadcast(sendBuffer);

		cout << "SessionCount : " << service->GetCurrentSessionCount() << endl;
		this_thread::sleep_for(83.33ms);
	}

	GThreadManager->Join();
}