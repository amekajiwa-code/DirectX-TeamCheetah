#pragma once
#include "Types.h"
struct Terrain_Cube
{
	Vec3   pos[8];
	Vec3   max;
	Vec3   min;
	Vec3   center;
	Vec3   axis[3];
	float     extent[3];
};