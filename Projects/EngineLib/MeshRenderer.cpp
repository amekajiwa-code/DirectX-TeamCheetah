#include "pch.h"
#include "MeshRenderer.h"
#include "InstancingBuffer.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

InstanceID MeshRenderer::GetInstanceID()
{
	return make_pair((uint64)_mesh.get(), (uint64)_material.get());
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

void MeshRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();
	if (shader == nullptr)
		return;

	// GlobalData
	shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	//auto t = TransformDesc{ GetTransform()->GetWorldMatrix() };
	//shader->PushTransformData(t);

	// Light
	//auto lightObj = MANAGER_SCENE()->GetCurrentScene()->GetLight();
	//if (lightObj)
		//shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Light
	_material->Update();

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();
	buffer->PushData();

	shader->DrawIndexedInstanced(0, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}
 