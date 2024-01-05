#pragma once
#include "Component.h"

class Model;
class Shader;
class Material;

class ModelRenderer : public Component
{
	using Super = Component;
public:
	ModelRenderer(shared_ptr<Shader> shader);
	virtual ~ModelRenderer();
private:
	shared_ptr<Shader>	_shader;
	shared_ptr<Model>	_model;
	uint8				_pass = 0;
public:
	shared_ptr<Model> GetModel() { return _model; }
	shared_ptr<Shader> GetShader() { return _shader; }
public:
	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
public:
	virtual void Update() override;
	virtual void LateUpdate() override;
};

