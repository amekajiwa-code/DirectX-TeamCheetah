#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	MANAGER_RESOURCES()->Init();
	_shader = make_shared<Shader>(L"Lighting.fx");
	MANAGER_RENDERER()->Init(_shader);

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
		_obj->GetMeshRenderer()->SetShader(_shader);
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
		_obj2->GetMeshRenderer()->SetShader(_shader);
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

	{
		//각 light별 색상을 결정하고 광원의 방향을 설정한다.
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		MANAGER_RENDERER()->PushLightData(lightDesc);
	}
	{
		//광원에 영향받는 정도를 설정한다.
		MaterialDesc desc;
		desc.ambient = Vec4(0.2f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		MANAGER_RENDERER()->PushMaterialData(desc);
		_obj->Update();
	}
	{
		//오브젝트 마다 다른 머티리얼을 적용 할 수 있다.
		MaterialDesc desc;
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		MANAGER_RENDERER()->PushMaterialData(desc);
		_obj2->Update();
	}
}

void Demo::Render()
{
}
