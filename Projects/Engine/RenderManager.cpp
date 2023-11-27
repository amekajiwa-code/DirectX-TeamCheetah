#include "pch.h"
#include "RenderManager.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

RenderManager* RenderManager::_instance = nullptr;

RenderManager::RenderManager()
{
	_device = GRAPHICS()->GetDevice();
	_deviceContext = GRAPHICS()->GetDeviceContext();
}

RenderManager::~RenderManager()
{
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;
	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::GetRederableObjects()
{
	_renderObjects.clear();

	auto& gameObjects = MANAGER_SCENE()->GetActiveScene()->GetGameObjects();

	for (auto& object : gameObjects)
	{
		auto meshRenderer = object->GetMeshRenderer();
		if (meshRenderer)
		{
			_renderObjects.push_back(object);
		}
	}
}

void RenderManager::RenderObjects()
{
	for (auto& rObject : _renderObjects)
	{
		auto meshRenderer = rObject->GetMeshRenderer();
		if (meshRenderer == nullptr)
		{
			continue;
		}
		auto transform = rObject->GetTransform();
		if (transform == nullptr)
		{
			continue;
		}

		_transformData.matWorld = transform->GetWorldMatrix();
		PushTransformData();

		auto mesh = meshRenderer->GetMesh();
		auto shader = meshRenderer->GetShader();
		auto texture = meshRenderer->GetTexture();

		Pipelineinfo info;
		info.vertexShader = shader->GetVertexShader();
		info.inputLayout = shader->GetInputLayout();
		info.pixelShader = shader->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info);


		_pipeline->SetVertexBuffer(mesh->GetVertexBuffer());
		_pipeline->SetIndexBuffer(mesh->GetIndexBuffer());

		_pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);

		_pipeline->SetTexture(0, SS_PixelShader, texture);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}

void RenderManager::Init()
{
	_pipeline = make_shared<Pipeline>();

	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraBuffer->CreateConstantBuffer();
	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformBuffer->CreateConstantBuffer();

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->CreateRasterizerState();
	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->CreateSamplerState();
	_blendState = make_shared<BlendState>(_device);
	_blendState->CreateBlendState();
}

void RenderManager::Update()
{
	GRAPHICS()->RenderBegin();
	{
		PushCameraData();
		GetRederableObjects();
		RenderObjects();
	}
	GRAPHICS()->RenderEnd();
}
