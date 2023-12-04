#pragma once
#include "engine/IExecute.h"
#include "engine/Geometry.h"

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void  Update() override;
	virtual void Render() override;
private:
	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vtxbuffer;
	shared_ptr<IndexBuffer> _idxbuffer;

	Vec3 _trans = Vec3(0.f, 0.f, 0.f);

	Matrix _world = Matrix::Identity;
};

