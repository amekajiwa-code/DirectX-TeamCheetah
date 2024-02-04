#pragma once
#include "ResourceBase.h"
#include "Geometry.h"

class Mesh : public ResourceBase
{
    using Super = ResourceBase;

public:
    Mesh();
    virtual ~Mesh();

	void CreateQuad();
	void CreateCube();
	void CreateGrid(int32 sizeX, int32 sizeZ);
	void CreateGridWithDistance(int32 sizeX, int32 sizeZ, float distance);
	void CreateSphere();

	shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }

private:
	void CreateBuffers();

private:
	// Mesh
	shared_ptr<Geometry<VertexTextureNormalTangentData>> _geometry;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

public:
	inline shared_ptr<Geometry<VertexTextureNormalTangentData>> GetGeo() {
		return _geometry;
	}
	inline void SetGeoMetry(shared_ptr<Geometry<VertexTextureNormalTangentData>> _geo) {
		_geometry = _geo;
	};
	void SetGeoMetryAndCreateBuffer(shared_ptr<Geometry<VertexTextureNormalTangentData>> _geo) {
		_geometry = _geo;
		CreateBuffers();
	}
};

