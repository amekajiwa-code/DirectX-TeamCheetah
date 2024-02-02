#pragma once
#include "InstancingBuffer.h"

class GameObject;

class InstancingManager
{
	InstancingManager();
	~InstancingManager();
	static InstancingManager* _instance;
public:
	static InstancingManager* GetInstance();
public:
	void Render(vector<shared_ptr<GameObject>>& gameObjects);
	void Clear() { _buffers.clear(); }
	void ClearData();
private:
	void RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects);
private:
	void AddData(InstanceID instanceId, InstancingData& data);
private:
	map<InstanceID/*instanceId*/, shared_ptr<InstancingBuffer>> _buffers;
};