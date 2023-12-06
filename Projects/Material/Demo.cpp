#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	MANAGER_RESOURCES()->Init();
	_shader = make_shared<Shader>(L"Lighting.fx");
	MANAGER_RENDERER()->Init(_shader);

	//Material
	{
		//생성
		shared_ptr<Material> material = make_shared<Material>();
		{
			//쉐이더 설정
			material->SetShader(_shader);
			//텍스쳐 설정
			wstring texAddr = RESOURCES_ADDR_TEXTURE;
			texAddr += L"veigar.jpg";
			auto tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"veigar", texAddr.c_str());
			material->SetDiffuseMap(tex);
		}
		//Desc
		MaterialDesc desc;
		//각 광원(환경광, 분산광, 반사광)에 해당하는 영향을 받는 정도를 설정한다 (0~1)
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		material->SetMaterialDesc(desc);
		//리소스 매니저에 머티리얼 추가
		MANAGER_RESOURCES()->AddResource<Material>(L"Veigar", material);
	}

	//camera
	{
		_camera = make_shared<GameObject>();
		_camera->Awake();
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraMove>());
		_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -10.f));
	}

	//Object
	{
		//생성 초기화
		_obj = make_shared<GameObject>();
		_obj->Awake();
		_obj->AddComponent(make_shared<MeshRenderer>());
		//Mesh Set
		{
			auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Sphere");
			_obj->GetMeshRenderer()->SetMesh(mesh);
		}
		//Material Set
		{
			auto material = MANAGER_RESOURCES()->GetResource<Material>(L"Veigar");
			_obj->GetMeshRenderer()->SetMaterial(material);
		}
	}

	//obj2
	{
		_obj2 = make_shared<GameObject>();
		_obj2->Awake();
		_obj2->GetTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
		_obj2->AddComponent(make_shared<MeshRenderer>());
		//Mesh Set
		{
			auto mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Cube");
			_obj2->GetMeshRenderer()->SetMesh(mesh);
		}
		//Material Set
		{
			auto material = MANAGER_RESOURCES()->GetResource<Material>(L"Veigar")->Clone();
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(0.33f);
			desc.diffuse = Vec4(0.33f);

			_obj2->GetMeshRenderer()->SetMaterial(material);
		}
	}

}

void Demo::Update()
{
	_camera->Update();
	MANAGER_RENDERER()->Update();

	//light
	{
		//각 light별 색상을 결정하고 광원의 방향을 설정한다.
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		MANAGER_RENDERER()->PushLightData(lightDesc);
	}
	//obj
	{
		_obj->Update();
	}
	{
		_obj2->Update();
	}
}

void Demo::Render()
{
}
