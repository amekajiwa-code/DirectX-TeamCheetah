#include "pch.h"
#include "Demo.h"
#include "CameraMove.h"

void Demo::Init()
{
	_shader = make_shared<Shader>(L"ConstantBuffer.fx");

	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, Color(1.0f, 0.f, 0.f, 1.f));
	_vtxbuffer = make_shared<VertexBuffer>();
	_vtxbuffer->CreateVertexBuffer(_geometry->GetVertices());
	_idxbuffer = make_shared<IndexBuffer>();
	_idxbuffer->CreateIndexBuffer(_geometry->GetIndices());

	//camera
	_camera = make_shared<GameObject>();
	_camera->Awake();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraMove>());
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.f, -2.f));
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

	uint32 stride = _vtxbuffer->GetStride();
	uint32 offset = _vtxbuffer->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _vtxbuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DC()->IASetIndexBuffer(_idxbuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	//Normal Color
	_shader->DrawIndexed(0, 0, _idxbuffer->GetCount(), 0, 0);
}
