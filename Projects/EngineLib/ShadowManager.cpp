#include "pch.h"
#include "ShadowManager.h"

ShadowManager::ShadowManager()
{
	rt.render_DSFormat = DXGI_FORMAT_R32_TYPELESS;
	rt.Create(GRAPHICS()->GetDevice(), 8192, 8192);
}

ShadowManager::~ShadowManager()
{
}

ShadowManager* ShadowManager::_instance = nullptr;


ShadowManager* ShadowManager::GetInstance()
{

	if (_instance == nullptr)
		_instance = new ShadowManager();

	return _instance;

}

void ShadowManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
	ClearData();
	CreateShadowData();

	RenderMeshRenderer(gameObjects);
	RenderModelRenderer(gameObjects);
	RenderAnimRenderer(gameObjects);
}

void ShadowManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		//if (vec.size() == 1)
		//{
		//	vec[0]->GetMeshRenderer()->RenderSingle();
		//}
		//else
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetMeshRenderer()->RenderInstancingShadow(buffer,_desc);
		}
	}
}


void ShadowManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelRenderer() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetModelRenderer()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		const auto& temp = gameObject->GetChildByName(L"Model");
		if (temp->GetModelRenderer())
		{
			const InstanceID instanceId = temp->GetModelRenderer()->GetInstanceID();
			cache[instanceId].push_back(gameObject);
		}
	}

	for (auto& pair : cache)
	{
		const vector<shared_ptr<GameObject>>& vec = pair.second;

		//if (vec.size() == 1)
		//{
		//	vec[0]->GetMeshRenderer()->RenderSingle();
		//}
		//else
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			if (vec[0]->GetModelRenderer() == nullptr)
			{
				shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
				vec[0]->GetChildByName(L"Model")->GetModelRenderer()->SetPass(5);
				vec[0]->GetChildByName(L"Model")->GetModelRenderer()->RenderInstancingShadow(buffer, _desc);
				vec[0]->GetChildByName(L"Model")->GetModelRenderer()->SetPass(1);
			}
			else
			{
				vec[0]->GetModelRenderer()->SetPass(5);
				shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
				vec[0]->GetModelRenderer()->RenderInstancingShadow(buffer, _desc);
				vec[0]->GetModelRenderer()->SetPass(1);
			}
		}
	}
}

void ShadowManager::RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
	map<InstanceID, vector<shared_ptr<GameObject>>> cache;

	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		if (gameObject->GetModelAnimator() == nullptr)
			continue;

		const InstanceID instanceId = gameObject->GetModelAnimator()->GetInstanceID();
		cache[instanceId].push_back(gameObject);
	}
	for (shared_ptr<GameObject>& gameObject : gameObjects)
	{
		const auto& temp = gameObject->GetChildByName(L"Model");
		if (temp->GetModelAnimator())
		{
			const InstanceID instanceId = temp->GetModelAnimator()->GetInstanceID();
			cache[instanceId].push_back(gameObject);
		}
	}

	for (auto& pair : cache)
	{
		shared_ptr<InstancedTweenDesc> tweenDesc = make_shared<InstancedTweenDesc>();

		const vector<shared_ptr<GameObject>>& vec = pair.second;

		//if (vec.size() == 1)
		//{
		//	vec[0]->GetModelAnimator()->RenderSingle();
		//}
		//else
		{
			const InstanceID instanceId = pair.first;

			for (int32 i = 0; i < vec.size(); i++)
			{
				const shared_ptr<GameObject>& gameObject = vec[i];
				InstancingData data;
				data.world = gameObject->GetTransform()->GetWorldMatrix();


				// INSTANCING
				if (gameObject->GetModelAnimator() == nullptr)
				{
					tweenDesc->tweens[i] = gameObject->GetChildByName(L"Model")->GetModelAnimator()->GetTweenDesc();
					data.world = gameObject->GetChildByName(L"Model")->GetTransform()->GetWorldMatrix();

				}
				else
				{
					tweenDesc->tweens[i] = gameObject->GetModelAnimator()->GetTweenDesc();

				}

				AddData(instanceId, data);
			}

			shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			if (vec[0]->GetModelAnimator() == nullptr)
			{
				vec[0]->GetChildByName(L"Model")->GetModelAnimator()->GetShader()->PushTweenData(*tweenDesc.get());
				shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
				vec[0]->GetChildByName(L"Model")->GetModelAnimator()->SetPass(6);
				vec[0]->GetChildByName(L"Model")->GetModelAnimator()->RenderInstancingShadow(buffer, _desc);
				vec[0]->GetChildByName(L"Model")->GetModelAnimator()->SetPass(2);
			}
			else
			{
				vec[0]->GetModelAnimator()->GetShader()->PushTweenData(*tweenDesc.get());
				vec[0]->GetModelAnimator()->SetPass(6);
				shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
				vec[0]->GetModelAnimator()->RenderInstancingShadow(buffer, _desc);
				vec[0]->GetModelAnimator()->SetPass(2);
			}
		}
	}
}

void ShadowManager::AddData(InstanceID instanceId, InstancingData& data)
{
	if (_buffers.find(instanceId) == _buffers.end())
		_buffers[instanceId] = make_shared<InstancingBuffer>();

	_buffers[instanceId]->AddData(data);
}

void ShadowManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		shared_ptr<InstancingBuffer>& buffer = pair.second;
		buffer->ClearData();
	}
}


void ShadowManager::CreateShadowData()
{
	float fWidthLength = 513 * 513;
	float fHeightLength = 513 * 513;
	float viewdis = sqrt(fWidthLength + fHeightLength);
	//Global
	auto light = MANAGER_SCENE()->GetCurrentScene()->GetLight()->GetLight()->GetLightDesc();
	Vec3 vecs = -(Vec3(light.direction) * 1000);
	auto shadowMat = Matrix::CreateLookAt(vecs, Vec3(0, 0, 0), Vec3(0, 1, 0));
	auto shadowProj = Matrix::CreateOrthographicOffCenter(-viewdis / 2, viewdis / 2, -viewdis / 2, viewdis / 2, 0.0, 1000);
	_desc.shadowView = shadowMat;
	_desc.shadowProj = shadowProj;
}

void ShadowManager::StartShadow() {
	Vec4 vClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	rt.Begin(GRAPHICS()->GetDeviceContext().Get(), vClearColor);
};
void ShadowManager::EndShadow() { rt.End(GRAPHICS()->GetDeviceContext().Get()); };
ID3D11ShaderResourceView* ShadowManager::GetShadowRTV() { return rt.GetDsvSRV(); };
void ShadowManager::SetShadow(shared_ptr<Shader> shader) {

	ShadowDesc shadowdesc;

	Matrix matTexture = Matrix(0.5f, 0.0f, 0.0f, 0.0f
		, 0.0f, -0.5f, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, 0.5f, 0.5f, 0.0f, 1.0f);

	Matrix matVPT1 = _desc.shadowView * _desc.shadowProj * matTexture;

	shadowdesc.mat = matVPT1;
	shader->PushShadowData(shadowdesc);
	shadow = shader->GetSRV("DepthMap");
	if (shadow) {
		shadow->SetResource(rt.GetDsvSRV());
	}
};