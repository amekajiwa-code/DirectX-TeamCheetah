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

}

void ModelRenderer::LateUpdate()
{
	if (_model == nullptr)
		return;

	if (GetGameObject()->GetModelAnimator() == nullptr ||
		GetGameObject()->GetModelAnimator()->GetPlay() == false)
	{
		//TOOL
		{
			auto rtv = GRAPHICS()->GetRenderTargetView(1);
			auto dsv = GRAPHICS()->GetDepthStencilView(1);

			float clearColor[4] = { 0.f,0.5f,0.f,0.5f };
			DC()->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());
			DC()->ClearRenderTargetView(rtv.Get(), clearColor);
			DC()->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
			DC()->RSSetViewports(1, &GRAPHICS()->GetViewport());
		}
	}

	//Bone
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	MANAGER_RENDERER()->PushBoneData(boneDesc);

	auto world = GetTransform()->GetWorldMatrix();
	MANAGER_RENDERER()->PushTransformData(TransformDesc{ world });

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

	//Tool
	{
		const auto& rtv = GRAPHICS()->GetRenderTargetView(0);
		const auto& dsv = GRAPHICS()->GetDepthStencilView(0);

		DC()->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());
		DC()->RSSetViewports(1, &GRAPHICS()->GetViewport());
	}
}
