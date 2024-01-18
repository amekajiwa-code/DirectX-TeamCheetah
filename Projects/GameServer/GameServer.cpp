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

	while (true)
	{
		//cout << "SessionCount : " << service->GetCurrentSessionCount() << endl;

		for (const auto& pair : GSessionManager.GetCharaInfoList()) {
			uint64 id = pair.first;
			CHARACTER_INFO info = pair.second;

			info._nextPos = GSessionManager.CalcNextPos(info);
			GSessionManager.UpdateCharaInfo(info);
		}

		SendBufferRef sendBuffer = ServerPacketHandler::Make_CHARACTER_INFO(GSessionManager.GetCharaInfoList());
		GSessionManager.Broadcast(sendBuffer);
		this_thread::sleep_for(100ms);
	}

	GThreadManager->Join();
}