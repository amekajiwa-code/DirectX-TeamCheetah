#pragma once
#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	//P T, P C
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);
public:
	//P N T
	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
public:
	//P N T Tangent
	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, int32 sizeX, int32 sizeZ);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
};

