#include "pch.h"
#include "RenderManager.h"

RenderManager* RenderManager::_instance = nullptr;

void RenderManager::Init(shared_ptr<Shader> shader)
{
	_shader = shader;

	//Global Set
	_globalBuffer = make_shared<ConstantBuffer<GlobalDesc>>();
	_globalBuffer->CreateConstantBuffer();
	_globalEffectBuffer = _shader->GetConstantBuffer("GlobalBuffer");
	//Transform Set
	_transformBuffer = make_shared<ConstantBuffer<TransformDesc>>();
	_transformBuffer->CreateConstantBuffer();
	_transformEffectBuffer = _shader->GetConstantBuffer("TransformBuffer");
	//light
	_lightBuffer = make_shared<ConstantBuffer<LightDesc>>();
	_lightBuffer->CreateConstantBuffer();
	_lightEffectBuffer = _shader->GetConstantBuffer("LightBuffer");
	//material
	_materialBuffer = make_shared<ConstantBuffer<MaterialDesc>>();
	_materialBuffer->CreateConstantBuffer();
	_materialEffectBuffer = _shader->GetConstantBuffer("MaterialBuffer");
}

void RenderManager::Update()
{
	PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
}

void RenderManager::PushGlobalData(const Matrix& view, const Matrix& projection)
{
	_globalDesc.V = view;
	_globalDesc.VInv = view.Invert();
	_globalDesc.P = projection;
	_globalDesc.VP = view * projection;
	_globalBuffer->CopyData(_globalDesc);
	_globalEffectBuffer->SetConstantBuffer(_globalBuffer->GetBuffer().Get());
}

void RenderManager::PushTransformData(const TransformDesc& desc)
{
	_transformDesc = desc;
	_transformBuffer->CopyData(_transformDesc);
	_transformEffectBuffer->SetConstantBuffer(_transformBuffer->GetBuffer().Get());
}

void RenderManager::PushLightData(const LightDesc& desc)
{
	_lightDesc = desc;
	_lightBuffer->CopyData(_lightDesc);
	_lightEffectBuffer->SetConstantBuffer(_lightBuffer->GetBuffer().Get());
}

void RenderManager::PushMaterialData(const MaterialDesc& desc)
{
	_materialDesc = desc;
	_materialBuffer->CopyData(_materialDesc);
	_materialEffectBuffer->SetConstantBuffer(_materialBuffer->GetBuffer().Get());
}

