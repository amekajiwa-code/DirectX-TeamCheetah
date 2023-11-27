#pragma once
#include "ResourceBase.h"

class Mesh : public ResourceBase
{
	using Super = ResourceBase;
public:
	Mesh();
	virtual ~Mesh();
private:
	ComPtr<ID3D11Device> _device;
private:
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer>	_indexBuffer;
public:
	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }
public:
	void CreateDefaultRectagnle();
};

