#pragma once
struct LavaSpriteDesc {
	vector<wstring> spritePathList;
	wstring ShaderName;
	wstring ShaderPath;
	float duration;
};
class StruectedLavaSprite : public MonoBehaviour
{
	vector<wstring> SpriteMaterialKey;
	vector<shared_ptr<Material>> MaterialList; // Need For Fast
	float duration = 0;
	float currentime = 0;
	int spriteIndex = 0;
private:
	StruectedLavaSprite() {};
public:
	StruectedLavaSprite(LavaSpriteDesc& desc);

public:
	virtual void Update() override;
};

