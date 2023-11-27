#pragma once
#include "ResourceBase.h"

struct Keyframe
{
	Vec2 offset{ 0,0 };
	Vec2 size{ 0,0 };
	float time = 0.f;
};

class Texture;

class Animation : public ResourceBase
{
	using Super = ResourceBase;
public:
	Animation();
	virtual ~Animation();
private:
	bool _loop = false;
	shared_ptr<Texture> _texture;
	vector<Keyframe> _keyframes;
public:
	virtual void Load(const wstring& path) override;
	virtual void Save(const wstring& path) override;
public:
	shared_ptr<Texture> GetTexture() const { return _texture; }
	Vec2				GetTextureSize() const;
	const Keyframe&		GeyKeyframe(int32 index);
	int32				GetKeyframeCount();
	bool IsLoop() const { return _loop; }
public:
	void SetLoop(const bool loop) { _loop = loop; }
	void SetTexture(shared_ptr<Texture> tex) { _texture = tex; }
public:
	void AddKeyframe(const Keyframe& keyframe);
};

