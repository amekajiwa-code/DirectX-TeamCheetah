#pragma once
#include "Sounds.h"
#include <list>

class SoundManager
{

	FMOD::System* fm_System;

	list<FMOD::Channel*> channelList;

	static SoundManager* _instance;
private:
	SoundManager() {

	}
public:
	SoundManager* GetInstance();
	~SoundManager();
};

