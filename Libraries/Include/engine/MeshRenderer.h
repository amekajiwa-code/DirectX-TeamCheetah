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
	shared_ptr<Mesh>		_mesh;
	shared_ptr<Material>	_material;
	shared_ptr<Shader>		_shader;
private:
	uint32 _stride = 0;
	uint32 _offset = 0;
public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	//legacy
	void SetTexture(shared_ptr<Texture> texture) {}
	void SetShader(shared_ptr<Shader> shader) {}
	const shared_ptr<Shader>& GetShader() const { return _shader; }
public:
	virtual void Start() override;
	virtual void Update() override;
};

