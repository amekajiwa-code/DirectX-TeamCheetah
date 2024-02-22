#include "pch.h"
#include "Skybox.h"

void Skybox::Start()
{

	if (skyBoxdesc == nullptr) {
		return ;
	}
	skySRV.resize(6);
	for (int i = 0; i < 6; ++i) {
		skyImages[i] = MANAGER_RESOURCES()->LoadResource<Texture>(L"SkyBox"+to_wstring(i), skyBoxdesc->resourceFilePath[i].c_str());
		skySRV[i] = skyImages[i]->GetTexture().Get();
	}

	GetOrAddTransform()->SetLocalPosition(Vec3(0, 0, 0));
	GetOrAddTransform()->SetLocalScale(Vec3(10000, 10000, 10000));
	AddComponent(make_shared<MeshRenderer>());
	mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Cube");
	GetMeshRenderer()->SetMesh(mesh);
	GetMeshRenderer()->SetPass(0);
	shader = make_shared<Shader>(skyBoxdesc->shaderPath);
	material = make_shared<Material>();
	material->SetShader(shader);
	//GetMeshRenderer()->SetShader(shader);
	GetMeshRenderer()->SetMaterial(material);
	GetMeshRenderer()->SetPass(0);
	srvarrayEff = shader->GetSRV("p_diffuseArray");
}

void Skybox::Update()
{
	GameObject::Update();

	//Global
	srvarrayEff->SetResourceArray(&skySRV.at(0), 0, 6);
	material->Update();
	shader->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });
	Matrix mat = Camera::S_MatView;
	mat._41 = 0;
	mat._42 = 0;
	mat._43 = 0;
	shader->PushGlobalData(mat, Camera::S_MatProjection);
	
	auto light = MANAGER_SCENE()->GetCurrentScene()->GetLight()->GetLight()->GetLightDesc();
	shader->PushLightData(light);

	UINT _stride = mesh->GetVertexBuffer()->GetStride();
	UINT _offset = mesh->GetVertexBuffer()->GetOffset();

	DC()->IASetVertexBuffers(0, 1, mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	DC()->IASetIndexBuffer(mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, 0, mesh->GetIndexBuffer()->GetCount(), 0, 0);
}
