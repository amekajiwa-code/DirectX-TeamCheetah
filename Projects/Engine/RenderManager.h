#pragma once
#include "RenderHelper.h"

class GameObject;

class RenderManager
{
private:
	static RenderManager* _instance;
public:
	static RenderManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new RenderManager();

		return _instance;
	}
private:
	RenderManager();
	~RenderManager();
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	shared_ptr<Pipeline> _pipeline;
private:
	//Camera
	CameraData									_cameraData;
	shared_ptr<ConstantBuffer<CameraData>>		_cameraBuffer;
	//SRT
	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_transformBuffer;
	//Animation
	AnimationData _animationData;
	shared_ptr<ConstantBuffer<AnimationData>> _animationBuffer;
private:
	shared_ptr<SamplerState>	_samplerState;
	shared_ptr<RasterizerState>	_rasterizerState;
	shared_ptr<BlendState>		_blendState;
private:
	vector<shared_ptr<GameObject>> _renderObjects;
private:
	void PushCameraData();
	void PushTransformData();
	void PushAnimationData();
	void GetRederableObjects();
	void RenderObjects();
public:
	void Init();
	void Update();
};

