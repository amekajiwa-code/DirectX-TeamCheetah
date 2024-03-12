#include "pch.h"
#include "Demo.h"

#include "DungeonScene.h"
#include "BaseScene.h"
#include "MainScene.h"

ClientServiceRef _service;

void Demo::Init(){
#pragma region Client Thread
	_service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,
		1);

	ASSERT_CRASH(_service->Start());

	for (int32 i = 0; i < 3; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					_service->GetIocpCore()->Dispatch();
				}
			}
		);
	}
#pragma endregion Client Thread

	shared_ptr<BaseScene> scene = make_shared<BaseScene>();
	scene->SetSceneName(L"BaseScene");
	//shared_ptr<Scene> scene = make_shared<DungeonScene>();
	//scene->SetSceneName(L"DungeonScene");
	//shared_ptr<Scene> scene = make_shared<MainScene>();
	MANAGER_SCENE()->ChangeScene(scene);
}

void Demo::Update()
{

}

void Demo::Render()
{
}
