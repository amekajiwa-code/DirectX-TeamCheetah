#include "pch.h"
#include "Mesh.h"

Mesh::Mesh() :Super(ResourceType::Mesh)
{
	_device = GRAPHICS()->GetDevice();
}

Mesh::~Mesh()
{
}

void Mesh::CreateDefaultRectagnle()
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_indexBuffer = make_shared<IndexBuffer>(_device);

	//Vertex data Create
	GeometryHelper::CreateRectangle(_geometry);
	//Vertexbuffer
	_vertexBuffer->CreateVertexBuffer(_geometry->GetVertices());
	//IndexBuffer
	_indexBuffer->CreateIndexBuffer(_geometry->GetIndices());
}
