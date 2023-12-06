#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	//���ҽ� �Ŵ��� �ʱ�ȭ
	MANAGER_RESOURCES()->Init();
	{
		//���ҽ� �߰�
		//���̴�
		MANAGER_RESOURCES()->AddResource(L"Default", make_shared<Shader>(L"Lighting.fx"));
		//�ؽ���
		wstring texAddr = RESOURCES_ADDR_TEXTURE;
		texAddr += L"veigar.jpg";
		auto tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"veigar", texAddr.c_str());
		MANAGER_RESOURCES()->AddResource<Texture>(L"Veigar", tex);
		//��Ƽ����
		{
			//����
			shared_ptr<Material> material = make_shared<Material>();
			{
				//���̴� ����
				auto shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
				material->SetShader(shader);
				//�ؽ��� ����
				auto tex = MANAGER_RESOURCES()->GetResource<Texture>(L"Veigar");
				material->SetDiffuseMap(tex);
			}
			//Desc
			MaterialDesc desc;
			//�� ����(ȯ�汤, �л걤, �ݻ籤)�� �ش��ϴ� ������ �޴� ������ �����Ѵ� (0~1)
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			material->SetMaterialDesc(desc);
			//���ҽ� �Ŵ����� ��Ƽ���� �߰�
			MANAGER_RESOURCES()->AddResource<Material>(L"Veigar", material);
		}
	}
	//���� �Ŵ��� �ʱ�ȭ
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
		//���� �ʱ�ȭ
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
			//Ư�� ������Ʈ�� ��Ƽ���� ����� Clone�� ���� �ν��Ͻ��� �ؾ��� (��)
			//���� ���� ��� ������ �����ȴ�.
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
		//�� light�� ������ �����ϰ� ������ ������ �����Ѵ�.
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
