#include "pch.h"
#include "Viewport.h"

Viewport::Viewport()
{
	SetViewport(g_gameDesc.width, g_gameDesc.height);
}

Viewport::Viewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	SetViewport(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
}

void Viewport::SetViewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	_viewport.TopLeftX = x;
	_viewport.TopLeftY = y;
	_viewport.Width = width;
	_viewport.Height = height;
	_viewport.MinDepth = minDepth;
	_viewport.MaxDepth = maxDepth;
}

void Viewport::RSSetViewport()
{
	DC()->RSSetViewports(1, &_viewport);
}
//World To Screen
Vec3 Viewport::Projcetion(const Vec3& pos, const Matrix& world, const Matrix& view, const Matrix& projcetion)
{
	Matrix wvp = world * view * projcetion;

	Vec3 rVector = Vec3::Transform(pos, wvp);
	{
		rVector.x = (rVector.x + 1.0f) * (_viewport.Width / 2) + _viewport.TopLeftX;
		rVector.y = (-rVector.y + 1.0f) * (_viewport.Height / 2) + _viewport.TopLeftY;
		rVector.z = rVector.z * (_viewport.MaxDepth - _viewport.MinDepth) + _viewport.MinDepth;
	}

	return rVector;
}
//Screen To World
Vec3 Viewport::UnProjcetion(const Vec3& pos, const Matrix& world, const Matrix& view, const Matrix& projcetion)
{
	Matrix wvp = world * view * projcetion;
	Matrix wvpInv = wvp.Invert();

	Vec3 rVector = pos;
	{
		rVector.x = 2.f * (rVector.x - _viewport.TopLeftX) / _viewport.Width - 1.f;
		rVector.y = -2.f * (rVector.y - _viewport.TopLeftY) / _viewport.Height + 1.f;
		rVector.z = ((rVector.z - _viewport.MinDepth) / (_viewport.MaxDepth - _viewport.MinDepth));

		rVector = Vec3::Transform(rVector, wvpInv);
	}

	return rVector;
}
