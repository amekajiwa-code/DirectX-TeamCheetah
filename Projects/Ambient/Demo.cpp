#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	MANAGER_RESOURCES()->Init();
	auto shader = make_shared<Shader>(L"GlobalTest.fx");
	MANAGER_RENDERER()->Init(shader);

	//camera
	_camera = make_shared<GameObject>();
	_camera->Awake();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraMove>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -10.f));

	//Object
	_obj = make_shared<GameObject>();
	_obj->Awake();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		//Shader set
		_obj->GetMeshRenderer()->SetShader(shader);
	}
	{
		//Mesh Set
		auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		//Texture Set
		wstring texAddr = RESOURCES_ADDR_TEXTURE;
		texAddr += L"veigar.jpg";
		auto tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"veigar", texAddr.c_str());
		_obj->GetMeshRenderer()->SetTexture(tex);
	}

	//obj2
	_obj2 = make_shared<GameObject>();
	_obj2->Awake();
	_obj2->GetTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		//Shader set
		_obj2->GetMeshRenderer()->SetShader(shader);
	}
	{
		//Mesh Set
		auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		//Texture Set
		wstring texAddr = RESOURCES_ADDR_TEXTURE;
		texAddr += L"veigar.jpg";
		auto tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"veigar", texAddr.c_str());
		_obj2->GetMeshRenderer()->SetTexture(tex);
	}

}

void Demo::Update()
{
	_camera->Update();

	MANAGER_RENDERER()->Update();
	_obj->Update();
	_obj2->Update();
}

void Demo::Render()
{
}
