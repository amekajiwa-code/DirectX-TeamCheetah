#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
	~Viewport();
private:
	D3D11_VIEWPORT _viewport;
public:
	void SetViewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
public:
	float GetWidth() const { return _viewport.Width; }
	float GetHeight() const { return _viewport.Height; }
public:
	void RSSetViewport();
	Vec3 Projcetion(const Vec3& pos, const Matrix& world, const Matrix& view, const Matrix& projcetion);
	Vec3 UnProjcetion(const Vec3& pos, const Matrix& world, const Matrix& view, const Matrix& projcetion);
};

