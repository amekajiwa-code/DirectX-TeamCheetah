#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"
#include "Converter.h"
#include "ImGuiManager.h"
#include "AssetManager.h"

void Demo::Init()
{
	//리소스 매니저 초기화
	MANAGER_RESOURCES()->Init();
	{
		_shader = make_shared<Shader>(L"GameObject.fx");
		MANAGER_RESOURCES()->AddResource<Shader>(L"Default", _shader);
	}
	//랜더 매니저 초기화
	MANAGER_RENDERER()->Init(_shader);
	//Camera
	{
		_camera = make_shared<GameObject>();
		_camera->Awake();
		_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -50.f));
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraMove>());
	}
	//light
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.diffuse = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.specular = Vec4(0.93, 0.91f, 0.67f, 1.0f);
		lightDesc.direction = Vec3(1.f, -1.f, -1.f);
		MANAGER_RENDERER()->PushLightData(lightDesc);
	}
}

void Demo::Update()
{
	_camera->Update();
	MANAGER_RENDERER()->Update();
}

void Demo::Render()
{
}
