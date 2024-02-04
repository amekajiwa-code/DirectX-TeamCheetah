#pragma once


struct SplatterDesc {
	std::wstring texPath[3] = { L"", };
	std::wstring texName[3] = { L"", };
	std::wstring normalPath[3] = { L"", };
	std::wstring normalName[3] = { L"", };

	std::wstring alphaPath = L"";
	std::wstring alphaName = L"";
};

class LayerSplatter {
	shared_ptr<Shader> _shader;
	 shared_ptr<Texture> splattingImages[3] = { nullptr, };
	 shared_ptr<Texture> splattingNormals[3] = { nullptr, };
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseA;
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseB;
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseC;
	 
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseNA;
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseNB;
	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseNC;

	 ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseAlpha;
	 shared_ptr<Texture> alphaImages = nullptr;
public:
	LayerSplatter() {};
	void Set(SplatterDesc desc,shared_ptr<Shader> shader);
	void PreUpdate();
};

