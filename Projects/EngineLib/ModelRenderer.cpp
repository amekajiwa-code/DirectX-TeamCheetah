#include "pch.h"
#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(shared_ptr<Shader> shader) 
	: Super(ComponentType::ModelRenderer), _shader(shader)
{
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::SetModel(shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}

void ModelRenderer::Update()
{
	/*
	if (_model == nullptr)
		return;

	//Bone
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	_shader->PushBoneData(boneDesc);

	auto world = GetTransform()->GetWorldMatrix();
	_shader->PushTransformData(TransformDesc{ world });
	_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	auto lightObj = MANAGER_SCENE()->GetCurrentScene()->GetLight();
	if (lightObj)
		_shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		//Bone Index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DC()->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetBuffer().GetAddressOf(),
			&stride, &offset);
		DC()->IASetIndexBuffer(mesh->indexBuffer->GetBuffer().Get(),
			DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
	*/
}

void ModelRenderer::LateUpdate()
{

}

void ModelRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_model == nullptr)
		return;

	//Bone
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	_shader->PushBoneData(boneDesc);
	_shader->PushGlobalData(Camera::S_MatView,Camera::S_MatProjection);
	auto lightObj = MANAGER_SCENE()->GetCurrentScene()->GetLight();
	if (lightObj)
		_shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		//Bone Index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		mesh->vertexBuffer->PushData();
		mesh->indexBuffer->PushData();
		buffer->PushData();

		_shader->DrawIndexedInstanced(0, _pass, mesh->indexBuffer->GetCount(), buffer->GetCount());
	}
}

MetaData& ModelRenderer::GetMetaData()
{
	if (_model)
	{
		shared_ptr<GameData> data = make_shared<ModelMetaData>();
		*data = _model->GetModelMetaData();

		_metaData.SetData(data);
	}

	return _metaData;
}

InstanceID ModelRenderer::GetInstanceID()
{
	return make_pair((uint64)_model.get(), (uint64)_shader.get());
}

void ModelRenderer::RenderInstancingShadow(shared_ptr<class InstancingBuffer>& buffer, ShadowViewDesc& desc)
{
	_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
	if (_model == nullptr)
		return;

	//Bone
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	_shader->PushBoneData(boneDesc);
	_shader->PushGlobalData(desc.shadowView, desc.shadowProj);
	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{

		//Bone Index
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		mesh->vertexBuffer->PushData();
		mesh->indexBuffer->PushData();
		buffer->PushData();

		_shader->DrawIndexedInstanced(0, _pass, mesh->indexBuffer->GetCount(), buffer->GetCount());
	}
}
