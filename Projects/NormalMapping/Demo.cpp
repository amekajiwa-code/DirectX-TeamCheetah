#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	//리소스 매니저 초기화
	MANAGER_RESOURCES()->Init();
	{
		//리소스 추가
		//쉐이더
		MANAGER_RESOURCES()->AddResource(L"Default", make_shared<Shader>(L"NormalMapping.fx"));
		//텍스쳐
		wstring texAddr = RESOURCES_ADDR_TEXTURE;
		texAddr += L"veigar.jpg";
		auto tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"veigar", texAddr.c_str());
		MANAGER_RESOURCES()->AddResource<Texture>(L"Veigar", tex);
		//머티리얼
		{
			//생성
			shared_ptr<Material> material = make_shared<Material>();
			{
				//쉐이더 설정
				auto shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
				material->SetShader(shader);
				//텍스쳐 설정
				auto tex = MANAGER_RESOURCES()->GetResource<Texture>(L"Veigar");
				material->SetDiffuseMap(tex);
				//노멀맵 텍스쳐 설정
				wstring adr = RESOURCES_ADDR_TEXTURE;
				adr += L"veigar_normal.png";
				auto normal = MANAGER_RESOURCES()->LoadResource<Texture>(L"VeigarNormal", adr);
				material->SetNormalMap(normal);
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
	}
	//랜더 매니저 초기화
	MANAGER_RENDERER()->Init(MANAGER_RESOURCES()->GetResource<Shader>(L"Default"));

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
			//특정 오브젝트의 머티리얼 변경시 Clone을 통해 인스턴싱을 해야함 (꼭)
			//하지 않을 경우 원본이 오염된다.
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
		lightDesc.specular = Vec4(1.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
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
