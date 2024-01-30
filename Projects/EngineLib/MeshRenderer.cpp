#include "pch.h"
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Start()
{
	if (_material != nullptr)
	{
		_shader = _material->GetShader();
	}
}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	_material->Update();

	_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	//Global
	_shader->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });

	_stride = _mesh->GetVertexBuffer()->GetStride();
	_offset = _mesh->GetVertexBuffer()->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	DC()->OMSetBlendState(nullptr, 0, -1);

	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}