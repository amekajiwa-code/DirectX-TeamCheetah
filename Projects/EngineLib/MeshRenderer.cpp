#include "pch.h"
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("Texture0")->SetResource(_texture->GetTexture().Get());
//
//	//Global
//	auto world = GetTransform()->GetWorldMatrix();
//	MANAGER_RENDERER()->PushTransformData(TransformDesc{ world });
//
//	// TEMP
//	//Vec3 lightDir = {0.f, 0.f, 1.f};
//	//_shader->GetVector("LightDir")->SetFloatVector((float*)&lightDir);
//	//_shader->GetMatrix("World")->SetMatrix((float*)&world);
//	//_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
//	//_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &stride, &offset);
//	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("DiffuseMap")->SetResource(_texture->GetTexture().Get());
//
//	//Global
//	auto world = GetTransform()->GetWorldMatrix();
//	MANAGER_RENDERER()->PushTransformData(TransformDesc{ world });
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &stride, &offset);
//	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();

	if (shader == nullptr)
		return;

	_material->Update();

	//Global
	MANAGER_RENDERER()->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });

	_stride = _mesh->GetVertexBuffer()->GetStride();
	_offset = _mesh->GetVertexBuffer()->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}