#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	_shader = make_shared<Shader>(L"Sampler.fx");
	_geometry = make_shared<Geometry<VertexTextureData>>();

	//GeometryHelper::CreateQuad(_geometry);
	//GeometryHelper::CreateCube(_geometry);
	//GeometryHelper::CreateSphere(_geometry);
	GeometryHelper::CreateGrid(_geometry, 100, 100);

	_vtxbuffer = make_shared<VertexBuffer>();
	_vtxbuffer->CreateVertexBuffer(_geometry->GetVertices());
	_idxbuffer = make_shared<IndexBuffer>();
	_idxbuffer->CreateIndexBuffer(_geometry->GetIndices());

	//camera
	_camera = make_shared<GameObject>();
	_camera->Awake();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraMove>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 50.f, -2.f));
	float as = 90.f;
	as *= PI / 180.f;
	_camera->GetTransform()->SetRotation(Vec3(as,0.f,0.f));

	wstring texAddr = RESOURCES_ADDR_TEXTURE;
	texAddr += L"night.png";
	_tex = MANAGER_RESOURCES()->LoadResource<Texture>(L"night", texAddr.c_str());
}

void Demo::Update()
{
	_camera->Update();
}

void Demo::Render()
{
	//fx 파일에 정의된 matrix를 가져와서 Set
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_tex->GetTexture().Get());

	enum ADDRESS_VALUE
	{
		ADDRESS_WRAP = 0,
		ADDRESS_MIRROR = 1,
		ADDRESS_CLAMP = 2,
		ADDRESS_BORDER = 3,
	};
	//Sampling test
	_shader->GetScalar("Address")->SetInt(ADDRESS_BORDER);

	uint32 stride = _vtxbuffer->GetStride();
	uint32 offset = _vtxbuffer->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _vtxbuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DC()->IASetIndexBuffer(_idxbuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	
	//tex
	_shader->DrawIndexed(0, 0, _idxbuffer->GetCount(), 0, 0);
	//wire
	//_shader->DrawIndexed(0, 1, _idxbuffer->GetCount(), 0, 0);
}
