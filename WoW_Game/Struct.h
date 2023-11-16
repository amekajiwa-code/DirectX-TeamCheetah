#pragma once
#include "Types.h"

struct Vertex
{
	Vec3 position;
	Vec2 uv;
	//Color color;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};