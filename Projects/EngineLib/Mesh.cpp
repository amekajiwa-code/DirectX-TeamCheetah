#include "pch.h"
#include "Mesh.h"
#include "GeometryHelper.h"

Mesh::Mesh()  : Super(ResourceType::Mesh)
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateQuad()
{
	//_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	_geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();

	GeometryHelper::CreateQuad(_geometry);
	CreateBuffers();
}

void Mesh::CreateCube()
{
	//_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	_geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();

	GeometryHelper::CreateCube(_geometry);
	CreateBuffers();
}

void Mesh::CreateGrid(int32 sizeX, int32 sizeZ)
{
	//_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	_geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();

	GeometryHelper::CreateGrid(_geometry, sizeX, sizeZ);
	CreateBuffers();
}

void Mesh::CreateGridWithDistance(int32 sizeX, int32 sizeZ, float distance)
{
	//_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	_geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();

	GeometryHelper::CreateGridWithDistance(_geometry, sizeX, sizeZ, distance);
	CreateBuffers();
}

void Mesh::CreateSphere()
{
	//_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	_geometry = make_shared<Geometry<VertexTextureNormalTangentData>>();

	GeometryHelper::CreateSphere(_geometry);
	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->CreateVertexBuffer(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->CreateIndexBuffer(_geometry->GetIndices());
}
