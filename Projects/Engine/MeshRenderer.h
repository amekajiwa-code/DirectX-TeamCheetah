#pragma once
#include "Component.h"

class Texture;

class MeshRenderer : public Component
{
	friend class RenderManager;
	using Super = Component;
public:
	MeshRenderer();
	MeshRenderer(shared_ptr<Pipeline> pipe);
	virtual ~MeshRenderer();
private:
	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;
	shared_ptr<Pipeline>			_pipeLine;
private:
	//Geometry & Mesh
	shared_ptr <Geometry<VertexTextureData>>	_geometry;
	shared_ptr<VertexBuffer>					_vertexBuffer;
	shared_ptr<IndexBuffer>	_indexBuffer;
	shared_ptr<InputLayout>	_inputLayout;
private:
	//VS
	shared_ptr<VertexShader>	_vertexShader;
	//PS
	shared_ptr<PixelShader>		_pixelShader;
	shared_ptr<Texture>			_texture;
private:
	void DefaultInit();
private:
	void CreateGeometry();
	void CreateVertexShader();
	void CreateInputLayout();
	void CreatePixelShader();
	void CreateTexture(const wstring& path);
public:
	virtual void Update() override;
};

