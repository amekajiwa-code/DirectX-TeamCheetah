#pragma once
#include "Sounds.h"
#include <list>

class SoundManager
{
//	list<pair<wstring,FMOD::Channel*>> channelList;
	shared_ptr<Transform> soundTransform;

	static SoundManager* _instance;
private:
	SoundManager() {

	}
public:
	SoundManager* GetInstance();
	~SoundManager();
public:
	void Init();
	void Update();
	void SetTransForm(shared_ptr<Transform> refTransform) {
		soundTransform = refTransform;
	}
//	void Pause();
//	void Resume();
//	void Stop();
};

