#pragma once
#include "Sounds.h"
#include <list>

class SoundManager
{
//	list<pair<wstring,FMOD::Channel*>> channelList;
	shared_ptr<Transform> soundTransform;
	FMOD_VECTOR prevPos = {1,1,1};
	vector <pair<Vec3*, FMOD::Channel*>> managed_channels;
	vector <FMOD::Channel*> managed_2Dchannels;
	static SoundManager* _instance;
private:
	SoundManager() {

	}
public:
	static SoundManager* GetInstance();
	~SoundManager();
public:
	void Init();
	void Update();
	void SetTransForm(shared_ptr<Transform> refTransform) {
		soundTransform = refTransform;
	}
	void AddChannel(Vec3* pos,FMOD::Channel* channel) {
		managed_channels.push_back(make_pair(pos,channel));
	}
	void AddChannel(FMOD::Channel* channel) {
		managed_2Dchannels.push_back(channel);
	}
//	void Pause();
//	void Resume();
//	void Stop();
};

