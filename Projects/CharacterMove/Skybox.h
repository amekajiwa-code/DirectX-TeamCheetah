#pragma once
struct SkyBoxDesc {

	std::wstring resourceFilePath[6] = { L"", };
	std::wstring shaderPath = L"";
	enum {
		SKY_Front = 0,
		SKY_Back = 1,
		SKY_Right = 2,
		SKY_Left = 3,
		SKY_UP = 4,
		SKY_DOWN = 5
	};
};
class Skybox :public GameObject
{
	SkyBoxDesc* skyBoxdesc = nullptr;
	array<shared_ptr<Texture>, 6>skyImages;
	std::vector<ID3D11ShaderResourceView*> skySRV;
	shared_ptr<Shader> shader;
	shared_ptr<Mesh> mesh; 
	shared_ptr<Material> material;
	ComPtr<ID3DX11EffectShaderResourceVariable> srvarrayEff;
public:
	Skybox() {};
	~Skybox() {};
public:

	void Set(SkyBoxDesc* desc) { skyBoxdesc = desc; };
	virtual void Start() override;
	virtual void Update() override;
};

