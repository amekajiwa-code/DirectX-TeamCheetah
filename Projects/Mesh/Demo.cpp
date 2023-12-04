#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	//camera
	_camera = make_shared<GameObject>();
	_camera->Awake();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraMove>());

	//Object
	_obj = make_shared<GameObject>();
	_obj->Awake();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		//Shader set
		auto shader = make_shared<Shader>(L"Normal.fx");
		_obj->GetMeshRenderer()->SetShader(shader);
	}
	{
		//Mesh Set
		MANAGER_RESOURCES()->Init();
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
}

void Demo::Update()
{
	_camera->Update();
	_obj->Update();
}

void Demo::Render()
{
}
