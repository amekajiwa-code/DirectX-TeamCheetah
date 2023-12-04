#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector<VertexColorData> vtx;
	vtx.resize(4);

	vtx[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vtx[0].color = color;

	vtx[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vtx[1].color = color;

	vtx[2].position = Vec3(0.5f, -0.5f, 0.f);
	vtx[2].color = color;

	vtx[3].position = Vec3(0.5f, 0.5f, 0.f);
	vtx[3].color = color;

	geometry->SetVertices(vtx);
	vector<uint32> idx = { 0,1,2,2,1,3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vtx;
	vtx.resize(4);

	vtx[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vtx[0].uv = Vec2(0.f,1.f);

	vtx[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vtx[1].uv = Vec2(0.f, 0.f);

	vtx[2].position = Vec3(0.5f, -0.5f, 0.f);
	vtx[2].uv = Vec2(1.f, 1.f);

	vtx[3].position = Vec3(0.5f, 0.5f, 0.f);
	vtx[3].uv = Vec2(1.f, 0.f);

	geometry->SetVertices(vtx);
	vector<uint32> idx = { 0,1,2,2,1,3 };
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry)
{
}
