#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"
//AI
#include "GameServerAI.h"

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

	GThreadManager->Launch([=]()
		{
			while (true)
			{
				GameServerAI gameAI;
				gameAI.Start();

				SendBufferRef sendBuffer = ServerPacketHandler::Make_MONSTER_INFO(GSessionManager.GetMobInfoList());
				GSessionManager.Broadcast(sendBuffer);
				this_thread::sleep_for(100ms);
			}
		});

	while (true)
	{
		cout << "SessionCount : " << service->GetCurrentSessionCount() << endl;
		this_thread::sleep_for(1000ms);
	}

	GThreadManager->Join();
}