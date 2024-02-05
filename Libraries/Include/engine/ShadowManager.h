#pragma once
#include "InstancingBuffer.h"
#include "RenderTarget.h"
class GameObject;
class Shader;

class ShadowManager
{
	ShadowManager();
	~ShadowManager();

	RenderTarget rt;
	ShadowViewDesc _desc;
	ComPtr<ID3DX11EffectShaderResourceVariable> shadow;

	static ShadowManager* _instance;
public:
	static ShadowManager* GetInstance();
public:
	void Render(vector<shared_ptr<GameObject>>& gameObjects);
	void Clear() { _buffers.clear(); }
	void ClearData();
	void CreateShadowData();
public:
	void StartShadow();
	void EndShadow();
	ID3D11ShaderResourceView* GetShadowRTV();
	void SetShadow(shared_ptr<Shader> shader);
private:
	void RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects);
private:
	void AddData(InstanceID instanceId, InstancingData& data);
private:
	map<InstanceID/*instanceId*/, shared_ptr<InstancingBuffer>> _buffers;
};

