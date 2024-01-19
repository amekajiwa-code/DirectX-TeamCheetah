#pragma once
#include "Component.h"
#include "ModelAnimation.h"

class Model;
class Shader;
class Material;

class ModelAnimator : public Component
{
	using Super = Component;
public:
	ModelAnimator();
	ModelAnimator(shared_ptr<Shader> shader);
	virtual ~ModelAnimator();
private:
	shared_ptr<Model>		_model;
	shared_ptr<Shader>	_shader;
	uint8				_pass = 0;
private:
	vector<AnimTransform>				_animTransforms;
	vector<shared_ptr<ModelAnimation>>	_anims;
	shared_ptr<ModelAnimation>			_currentAnim;
	shared_ptr<ModelAnimation>			_nextAnim;

	ComPtr<ID3D11Texture2D>				_texture;
	ComPtr<ID3D11ShaderResourceView>	_srv;
private:
	KeyframeDesc _keyFrameDesc;
	TweenDesc	_tweenDesc;
	uint16		_animCount = 0;
	bool			_isPlay = false;
	bool			_isLoop = false;
	bool			_isAnimationEnd = false;
	float		_timePerFrame = 0.f;
	float		_duration = 0.f;
private:
	void CreateTexture();
	void CreateAnimationTransform(uint32 index);
public:
	void SetModel(shared_ptr<Model> model) { _model = model; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
	void SetPass(uint8 pass) { _pass = pass; }
public:
	void	 SetAnimationByName(wstring name);
	void	 SetTweenCurrentAnimationByName(wstring name);
	void	 SetTweenNextAnimationByName(wstring name);
public:
	void SetPlay(bool play) { _isPlay = play; }
	bool GetPlay() const { return _isPlay; }
	void SetLoop(bool loop) { _isLoop = loop; }
	bool GetLoop() const { return _isLoop; }
	bool GetAnimationend() const{ return _isAnimationEnd; }
public:
	KeyframeDesc& GetKeyFrame() { return _keyFrameDesc; }
	TweenDesc& GetTweenDesc() { return _tweenDesc; }
public:
	virtual void Start() override;
	virtual void Update() override;
};

