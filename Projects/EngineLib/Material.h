#pragma once
#include "ResourceBase.h"

class Material : public ResourceBase
{
	using Super = ResourceBase;
	friend class MeshRenderer;
	friend class ModelRenderer;
public:
	Material();
	virtual ~Material();
private:
	MaterialDesc		_desc;
	shared_ptr<Shader>	_shader;
	shared_ptr<Texture> _diffuseMap;
	shared_ptr<Texture> _specularMap;
	shared_ptr<Texture> _normalMap;
private:
	ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _specularEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _normalEffectBuffer;
public:
	MaterialDesc& GetMaterialDesc() { return _desc; }
	shared_ptr<Shader> GetShader() { return _shader; }
	shared_ptr<Texture> GetDiffuseMap() { return _diffuseMap; }
	shared_ptr<Texture> GetNormalMap() { return _normalMap; }
	shared_ptr<Texture> GetSpecularMap() { return _specularMap; }
public:
	void SetMaterialDesc(const MaterialDesc& desc) { _desc = desc; }
	void SetShader(shared_ptr<Shader> shader);
	void SetDiffuseMap(shared_ptr<Texture> diffuseMap) { _diffuseMap = diffuseMap; }
	void SetNormalMap(shared_ptr<Texture> normalMap) { _normalMap = normalMap; }
	void SetSpecularMap(shared_ptr<Texture> specularMap) { _specularMap = specularMap; }
public:
	void Update();
	shared_ptr<Material> Clone();
};

