#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"
#include "engine\Utils.h"
#include "engine/Warrior.h"
#include "engine/CoreHound.h"

void Demo::Init()
{
	//리소스 매니저 초기화
	MANAGER_RESOURCES()->Init();
	{
		_shader = make_shared<Shader>(L"TweenAnimation.fx");
		MANAGER_RESOURCES()->AddResource<Shader>(L"Default", _shader);
		wstring dTex = RESOURCES_ADDR_TEXTURE;
		dTex += L"Effect/noise.png";
		_dissolve = MANAGER_RESOURCES()->GetOrAddTexture(L"Dissolve", dTex);
	}

	//랜더 매니저 초기화
	MANAGER_RENDERER()->Init(_shader);

	//light
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(1.f, 1.f, 1.f, 1.0f);
		lightDesc.diffuse = Vec4(1.f, 1.f, 1.f, 0.5f);
		lightDesc.specular = Vec4(1.0, 1.0f, 1.0f, 1.0f);

		{
			Transform tf;
			Vec3 rv(0.f);
			rv.x += ::XMConvertToRadians(45.f);
			rv.y += ::XMConvertToRadians(90.f);
			rv.z = 0;
			tf.SetRotation(rv);
			tf.UpdateTransform();
			Vec3 sundir = tf.GetLookVector();
			sundir.Normalize();
			lightDesc.direction = sundir;
		}

		MANAGER_RENDERER()->PushLightData(lightDesc);
	}

	//Plane
	{
		_map = make_shared<GameObject>();
		_map->Awake();
		{
			shared_ptr<Mesh> plane = make_shared<Mesh>();
			plane->CreateQuad();
			shared_ptr<Material> mtrl = make_shared<Material>();
			_terShader = make_shared<Shader>(L"GameTerrain.fx");
			mtrl->SetShader(_terShader);

			wstring tex = RESOURCES_ADDR_TEXTURE;
			tex += L"grass.jpg";
			shared_ptr<Texture> grass = make_shared<Texture>();
			grass->Load(tex);

			{
				MaterialDesc desc;
				desc.ambient = Color(1.0f,1.0f,1.0f,1.0f);
				mtrl->SetMaterialDesc(desc);
			}

			mtrl->SetDiffuseMap(grass);
			mtrl->SetNormalMap(nullptr);

			shared_ptr<MeshRenderer> _renderer = make_shared<MeshRenderer>();
			_renderer->SetMesh(plane);
			_renderer->SetMaterial(mtrl);
			_map->AddComponent(_renderer);
		}
		_map->Start();
		_map->GetTransform()->SetScale(Vec3(100, 100, 1));

		Vec3 rot = _map->GetTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		_map->GetTransform()->SetRotation(rot);
	}

	//Character
	{
		_warrior = make_shared<Warrior>();
		_warrior->Awake();
		_warrior->Start();
	}
	//Enemy
	{
		_coreHound = make_shared<CoreHound>();
		_coreHound->Awake();
		_coreHound->Start();
		_coreHound->GetTransform()->SetLocalPosition(Vec3(0, 0, 20));
	}
}

void Demo::Update()
{
	MANAGER_RENDERER()->Update();
	static float dt = 0.f;

	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::KEY_1))
	{
		if (_isdisv)
		{
			_isdisv = false;
		}
		else
		{
			_isdisv = true;
		}
	}
	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::KEY_2))
	{
		if (dt >= 1.0f)
		{
			dt = 0.f;
		}

		_isdisv = false;
	}

	if (_isdisv)
	{
		dt += MANAGER_TIME()->GetDeltaTime() * 0.35f;
	}

	_shader->GetSRV("dissolve")->SetResource(_dissolve->GetTexture().Get());
	_shader->GetScalar("time")->SetFloat(dt);

	{
		_map->Update();
	}
	{
		_warrior->FixedUpdate();
		_warrior->Update();
		_warrior->LateUpdate();
	}
	{
		_coreHound->FixedUpdate();
		_coreHound->Update();
		_coreHound->LateUpdate();
	}



	if (MANAGER_INPUT()->GetButtonDown(KEY_TYPE::PrintScreen))
	{
		Utils::ScreenShot(DC(), L"");
	}
}

void Demo::Render()
{
}
