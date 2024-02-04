#pragma once
//class Light : public MonoBehaviour
//{
//public:
//	Light(){}
//	virtual ~Light(){}
//private:
//	shared_ptr<Shader> _shader;
//public:
//	void SetShader(const shared_ptr<Shader> shader) { _shader = shader; }
//public:
//	virtual void Start() override;
//	virtual void Update() override;
//};

class Light : public Component
{
public:
	Light();
	virtual ~Light();

	virtual void Update();

public:
	LightDesc& GetLightDesc() { return _desc; }

	void SetLightDesc(LightDesc& desc) { _desc = desc; }
	void SetAmbient(const Color& color) { _desc.ambient = color; }
	void SetDiffuse(const Color& color) { _desc.diffuse = color; }
	void SetSpecular(const Color& color) { _desc.specular = color; }
	void SetEmissive(const Color& color) { _desc.emissive = color; }
	void SetLightDirection(Vec3 direction) { _desc.direction = direction; }

private:
	LightDesc _desc;
};


