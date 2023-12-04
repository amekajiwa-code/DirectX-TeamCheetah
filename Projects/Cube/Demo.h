#pragma once
#include "engine/IExecute.h"

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	//obj
	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vtxbuffer;
	shared_ptr<IndexBuffer> _idxbuffer;

	Vec3 _trans = Vec3(0.f, 0.f, 0.f);

	Matrix _world = Matrix::Identity;
	Matrix _view = Matrix::Identity;
	Matrix _projection = Matrix::Identity;
	//Camera
	shared_ptr<GameObject> _camera;
	shared_ptr<Texture> _tex;
};

