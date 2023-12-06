#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Material;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();
private:
	shared_ptr<Mesh>	_mesh;
	shared_ptr<Material> _material;
private:
	uint32 _stride;
	uint32 _offset;
	//shared_ptr<Texture> _texture;
	//shared_ptr<Shader>	_shader;
public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	//legacy
	void SetTexture(shared_ptr<Texture> texture) {}
	void SetShader(shared_ptr<Shader> shader) {}
public:
	virtual void Update() override;
};

