#pragma once
#include "fmod\fmod.h"
#include "fmod\fmod.hpp"
#include "fmod\fmod_errors.h"

//class Sound : public ResourceBase
//{
//	using Super = ResourceBase;
//
//	//need each n files to create;
//	FMOD::Sound* fm_Sound;
//
//public:
//	Sound();
//	~Sound();
//public:
//	bool Init();
//	bool Frame();
//	void Load(const wstring& path);
//	bool Release();
//	bool Pause();
//	bool Resume();
//	FMOD::Channel Play(bool doLoop = false);
//	FMOD::Channel PlayEffect();
//	bool Stop();
//	bool Volume(float vol);
//};