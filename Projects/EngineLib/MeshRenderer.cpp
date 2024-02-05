#include "pch.h"
#include "MeshRenderer.h"
#include "InstancingBuffer.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}
#pragma region Need To DepreCate

Matrix MeshRenderer::ShadowUpdate() {

	if (_mesh == nullptr || _material == nullptr)
		return Matrix::Identity;

	auto shader = _material->GetShader();

	if (shader == nullptr)
		return Matrix::Identity;

	float fWidthLength = 513 * 513;
	float fHeightLength = 513 * 513;
	float viewdis = sqrt(fWidthLength + fHeightLength);
	//Global
	auto light = MANAGER_SCENE()->GetCurrentScene()->GetLight()->GetLight()->GetLightDesc();
	Vec3 vecs = -(Vec3(light.direction) * 1000);
	auto shadowMat = Matrix::CreateLookAt(vecs, Vec3(0, 0, 0), Vec3(0, 1, 0));
	auto shadowProj = Matrix::CreateOrthographicOffCenter(-viewdis / 2, viewdis / 2, -viewdis / 2, viewdis / 2, 0.0, 1000);
	_stride = _mesh->GetVertexBuffer()->GetStride();
	_offset = _mesh->GetVertexBuffer()->GetOffset();
	shader->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });
	shader->PushGlobalData(shadowMat, shadowProj);

	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);

	Matrix matTexture = Matrix(0.5f, 0.0f, 0.0f, 0.0f
		, 0.0f, -0.5f, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, 0.5f, 0.5f, 0.0f, 1.0f);

	Matrix matWVPT1 = GetTransform()->GetWorldMatrix() * shadowMat * shadowProj * matTexture;
	return matWVPT1;
}
void MeshRenderer::LegacyUpdate()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();

	if (shader == nullptr)
		return;

	_material->Update();

	//Global
	shader->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });
	shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
	auto light = MANAGER_SCENE()->GetCurrentScene()->GetLight()->GetLight()->GetLightDesc();
	shader->PushLightData(light);

	_stride = _mesh->GetVertexBuffer()->GetStride();
	_offset = _mesh->GetVertexBuffer()->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}

#pragma endregion
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
	//if (_mesh == nullptr || _material == nullptr)
	//	return;

	//_material->Update();

	//_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	////Global
	//_shader->PushTransformData(TransformDesc{ GetTransform()->GetWorldMatrix() });

	//_stride = _mesh->GetVertexBuffer()->GetStride();
	//_offset = _mesh->GetVertexBuffer()->GetOffset();

	//DC()->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &_stride, &_offset);
	//DC()->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	//DC()->OMSetBlendState(nullptr, 0, -1);

	//_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
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
	auto lightObj = MANAGER_SCENE()->GetCurrentScene()->GetLight();
	if (lightObj)
		//shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Light
	_material->Update();

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();
	buffer->PushData();

	shader->DrawIndexedInstanced(0, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}

void MeshRenderer::RenderInstancingShadow(shared_ptr<class InstancingBuffer>& buffer,ShadowViewDesc& desc)
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();
	if (shader == nullptr)
		return;

	// GlobalData
	shader->PushGlobalData(desc.shadowView,desc.shadowProj);

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();
	buffer->PushData();

	shader->DrawIndexedInstanced(0, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}
