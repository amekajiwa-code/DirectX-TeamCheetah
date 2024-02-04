#include "pch.h"
#include "StruectedLavaSprite.h"

StruectedLavaSprite::StruectedLavaSprite(LavaSpriteDesc& desc)
{
	duration = desc.duration;
	SpriteMaterialKey.reserve(desc.spritePathList.size());
	for (auto c : desc.spritePathList) {
		size_t found = c.find_last_of(L"/");
		wstring key = c.substr(found + 1);
		SpriteMaterialKey.push_back(key);
		auto texture = MANAGER_RESOURCES()->LoadResource<Texture>(key.c_str(), c.c_str());

		shared_ptr<Shader> shader;
		if (desc.ShaderName.empty() || desc.ShaderPath.empty()) {
			shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		}
		else {
			shader = make_shared<Shader>(desc.ShaderPath);
			//shader = MANAGER_RESOURCES()->LoadResource<Shader>(desc.ShaderName.c_str(), desc.ShaderPath.c_str());
		}
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		//텍스쳐 설정
		material->SetDiffuseMap(texture);
		//노멀맵 텍스쳐 설정
		auto normal = MANAGER_RESOURCES()->GetResource <Texture>(L"DefaultNormal");
		material->SetNormalMap(normal);
		auto spec = MANAGER_RESOURCES()->GetResource <Texture>(L"DefaultSpecular");
		material->SetSpecularMap(spec);
		MANAGER_RESOURCES()->AddResource(key, material);
		MaterialList.push_back(material);
	}
}
void StruectedLavaSprite::Update()
{
	auto render = GetGameObject()->GetMeshRenderer();
	if (render == nullptr) {
		return;
	}
	auto time=MANAGER_TIME()->GetDeltaTime();
	currentime += time;
	if ((duration/SpriteMaterialKey.size()) < currentime) {
		currentime -= (duration / SpriteMaterialKey.size());
		++spriteIndex;
		if (spriteIndex >= SpriteMaterialKey.size()) {
			spriteIndex = 0;  
		}
	}
	render->SetMaterial(MaterialList[spriteIndex]);
	return;
}
;
