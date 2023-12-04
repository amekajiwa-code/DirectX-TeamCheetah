#pragma once
#include "Component.h"

class Mesh;
class Shader;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();
private:
	shared_ptr<Mesh>	_mesh;
	shared_ptr<Texture> _texture;
	shared_ptr<Shader>	_shader;
public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
public:
	virtual void Update() override;
};

