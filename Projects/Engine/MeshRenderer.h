#pragma once
#include "Component.h"

class Texture;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();
private:
	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>	_deviceContext;
	shared_ptr<Pipeline>			_pipeLine;
private:
	//Geometry & Mesh
	shared_ptr <Geometry<VertexTextureData>>	_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>					_indexBuffer;
	shared_ptr<InputLayout>					_inputLayout;
private:
	//Material
	//VS
	shared_ptr<VertexShader>		_vertexShader;
	//RS
	shared_ptr<RasterizerState>	_rasterizerState;
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	shared_ptr<Texture>			_texture;
	shared_ptr<SamplerState>		_samplerState;
	//OM
	shared_ptr<BlendState>		_blendState;
private:
	CameraData								_cameraData;
	shared_ptr<ConstantBuffer<CameraData>>		_cameraBuffer;

	TransformData								_transformData;
	shared_ptr<ConstantBuffer<TransformData>>	_transformBuffer;
private:
	void DefaultInit();
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
	virtual void Update() override;
	void Render(shared_ptr<Pipeline> pipeline);
};

