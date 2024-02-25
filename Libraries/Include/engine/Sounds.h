#pragma once
#include "fmod\fmod.h"
#include "fmod\fmod.hpp"
#include "fmod\fmod_errors.h"

class Sound : public ResourceBase
{
	using Super = ResourceBase;

	//need each n files to create;
	FMOD::Sound* fm_Sound;
	float volume=100;
public:
	Sound();
	~Sound();
public:
	void Load(const wstring& path);
	FMOD::Channel* Play(bool doLoop);
	FMOD::Channel* Play3D(bool doLoop, Vec3 pos, Vec3 vel);
	void PlayEffect();
	void Play3DEffect(Vec3 pos, Vec3 vel);
	
	void SetVolume(float vol) {volume = vol;};
};