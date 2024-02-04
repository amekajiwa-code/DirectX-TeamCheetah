#include "pch.h"
#include "LayerSplatter.h"

void LayerSplatter::Set(SplatterDesc desc,shared_ptr<Shader> shader)
{
	_shader = shader;
	for (int i = 0; i < 3; i++) {
		splattingImages[i] = MANAGER_RESOURCES()->LoadResource<Texture>(desc.texName[i].c_str(), desc.texPath[i].c_str());
		if(desc.normalName[i]!=L"")splattingNormals[i] = MANAGER_RESOURCES()->LoadResource<Texture>(desc.normalName[i].c_str(), desc.normalPath[i].c_str());
	}
	alphaImages = MANAGER_RESOURCES()->LoadResource<Texture>(desc.alphaName.c_str(), desc.alphaPath.c_str());

	_diffuseA = _shader->GetSRV("SplattingMapA");
	_diffuseB = _shader->GetSRV("SplattingMapB");
	_diffuseC = _shader->GetSRV("SplattingMapC");

	_diffuseNA = _shader->GetSRV("SplattingMapNormalA");
	_diffuseNB = _shader->GetSRV("SplattingMapNormalB");
	_diffuseNC = _shader->GetSRV("SplattingMapNormalC");
	_diffuseAlpha = _shader->GetSRV("SplattingAlpha");
}
void LayerSplatter::PreUpdate() {
	HRESULT hr;
		hr = _diffuseA->SetResource(splattingImages[0]->GetTexture().Get());
		hr = _shader->GetSRV("SplattingMapB")->SetResource(splattingImages[1]->GetTexture().Get());
		hr = _shader->GetSRV("SplattingMapC")->SetResource(splattingImages[2]->GetTexture().Get());

		//_diffuseA->SetResource(splattingImages[0]->GetTexture().Get());
		//_diffuseB->SetResource(splattingImages[1]->GetTexture().Get());
		//_diffuseC->SetResource(splattingImages[2]->GetTexture().Get());

		if (splattingNormals[0])
		_diffuseNA->SetResource(splattingNormals[0]->GetTexture().Get());
		if (splattingNormals[1])
		_diffuseNB->SetResource(splattingNormals[1]->GetTexture().Get());
		if (splattingNormals[2])
		_diffuseNC->SetResource(splattingNormals[2]->GetTexture().Get());

		hr = _diffuseAlpha->SetResource(alphaImages->GetTexture().Get());
	
}
