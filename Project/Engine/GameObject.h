#pragma once

class MonoBehaviour;
class Camera;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~GameObject();
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
private:
	//Geometry
	shared_ptr <Geometry<VertexTextureData>>	_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>						_indexBuffer;
	shared_ptr<InputLayout>						_inputLayout;
private:
	//VS
	shared_ptr<VertexShader>					_vertexShader;
private:
	CameraData									_cameraData;
	shared_ptr<ConstantBuffer<CameraData>>		_cameraBuffer;

	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_transformBuffer;
private:
	//RS
	shared_ptr<RasterizerState>	_rasterizerState;
private:
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	shared_ptr<Texture>			_texture;
	shared_ptr<SamplerState>	_samplerState;
private:
	//OM
	shared_ptr<BlendState>		_blendState;
protected:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
public:
	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Transform> GetOrAddTransform();
	shared_ptr<Camera> GetCamera();
public:
	void AddComponent(shared_ptr<Component> component);
private:
	void DefaultInit();
	void DefaultPipelineSet();
private:
	void CreateGeometry();
	void CreateVertexShader();
	void CreateInputLayout();
	void CreateConstantBuffer();
	void CreateRasterizerState();
	void CreatePixelShader();
	void CreateTexture(const wstring& path);
	void CreateSamplerState();
	void CreateBlendState();
public:
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
public:
	virtual void Render(shared_ptr<Pipeline> pipeline);
};

