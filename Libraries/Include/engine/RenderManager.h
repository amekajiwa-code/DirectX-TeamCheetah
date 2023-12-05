#pragma once

class Shader;

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
	RenderManager(){}
	~RenderManager(){}
private:
	shared_ptr<Shader> _shader;
private:
	GlobalDesc _globalDesc;
	shared_ptr<ConstantBuffer<GlobalDesc>> _globalBuffer;
	ComPtr<ID3DX11EffectConstantBuffer> _globalEffectBuffer;
private:
	TransformDesc _transformDesc;
	shared_ptr<ConstantBuffer<TransformDesc>> _transformBuffer;
	ComPtr<ID3DX11EffectConstantBuffer> _transformEffectBuffer;
private:
	LightDesc _lightDesc;
	shared_ptr<ConstantBuffer<LightDesc>> _lightBuffer;
	ComPtr<ID3DX11EffectConstantBuffer> _lightEffectBuffer;
private:
	MaterialDesc _materialDesc;
	shared_ptr<ConstantBuffer<MaterialDesc>> _materialBuffer;
	ComPtr<ID3DX11EffectConstantBuffer> _materialEffectBuffer;
public:
	void PushGlobalData(const Matrix& view, const Matrix& projection);
	void PushTransformData(const TransformDesc& desc);
	void PushLightData(const LightDesc& desc);
	void PushMaterialData(const MaterialDesc& desc);
public:
	void Init(shared_ptr<Shader> shader);
	void Update();
};

