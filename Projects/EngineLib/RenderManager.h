#pragma once

class Shader;

struct GlobalDesc
{
	Matrix V = Matrix::Identity;
	Matrix P = Matrix::Identity;
	Matrix VP = Matrix::Identity;
};

struct TransformDesc
{
	Matrix W = Matrix::Identity;
};

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
public:
	void PushGlobalData(const Matrix& view, const Matrix& projection);
	void PushTransformData(const TransformDesc& desc);
public:
	void Init(shared_ptr<Shader> shader);
	void Update();
};

