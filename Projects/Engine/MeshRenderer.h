#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public Component
{
	friend class RenderManager;
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();
private:
	shared_ptr<Mesh>		_mesh;
	shared_ptr<Material>	_material;
public:
	//Mesh : vertexbuffer, indexbuffer, geometry data
	shared_ptr<Mesh>		GetMesh() { return _mesh; }
	//Matertial : shader, texture
	shared_ptr<Material>	GetMaterial() { return _material; }
	//Shader : vertexshader, inputlayout, pixelshader
	shared_ptr<Shader>		GetShader() { return _material->GetShader(); }
	shared_ptr<Texture>		GetTexture() { return _material->GetTexture(); }
public:
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
	void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); }
};

