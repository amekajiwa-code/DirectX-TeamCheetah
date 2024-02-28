#include "pch.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;

SoundManager* SoundManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new SoundManager();

	return _instance;
}

SoundManager::~SoundManager()
{

	g_fmSystem->close();
	g_fmSystem->release();
}

void SoundManager::Init()
{
	if (!managed_2Dchannels.empty()) {
		for (auto c : managed_2Dchannels) {
			c->setPaused(true);
//			c->stop();
		}
		managed_2Dchannels.clear();
	}
	if (!managed_channels.empty()) {
		for (auto c : managed_channels) {
			c.second->setPaused(true);
//			c.second->stop();
		}
		managed_channels.clear();
	}
	if (g_fmSystem == nullptr) {
		FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_LOG);
		FMOD::System_Create(&g_fmSystem);
		FMOD_RESULT fr= g_fmSystem->init(64, FMOD_INIT_NORMAL, nullptr);
		g_fmSystem->set3DSettings(0.01, 0.01, 0.01);
	}
}

void SoundManager::Update()
{	
	if (soundTransform) {


		FMOD_3D_ATTRIBUTES _3DsoundDesc;
		_3DsoundDesc.position.x = soundTransform->GetLocalPosition().x;
		_3DsoundDesc.position.y = soundTransform->GetLocalPosition().y;
		_3DsoundDesc.position.z = soundTransform->GetLocalPosition().z;
		_3DsoundDesc.up.x = soundTransform->GetUpVector().x;
		_3DsoundDesc.up.y = soundTransform->GetUpVector().y;
		_3DsoundDesc.up.z = soundTransform->GetUpVector().z;
		_3DsoundDesc.forward.x = soundTransform->GetLookVector().x;
		_3DsoundDesc.forward.y = soundTransform->GetLookVector().y;
		_3DsoundDesc.forward.z = soundTransform->GetLookVector().z;
		_3DsoundDesc.velocity.x = _3DsoundDesc.position.x / prevPos.x;
		_3DsoundDesc.velocity.y = _3DsoundDesc.position.y / prevPos.y;
		_3DsoundDesc.velocity.z = _3DsoundDesc.position.z / prevPos.z;
		g_fmSystem->set3DListenerAttributes(0, &_3DsoundDesc.position, &_3DsoundDesc.velocity, &_3DsoundDesc.forward, &_3DsoundDesc.up);
		prevPos = _3DsoundDesc.position;
	}
	for (int i = 0; i < managed_channels.size(); ++i) {
		bool isfin;
		managed_channels[i].second->isPlaying(&isfin);
		if(!isfin){
			auto it = managed_channels.begin() + i;
			managed_channels.erase(it);
			--i;
			continue;
		}
		FMOD_VECTOR vel = { 1,1,1 };
		Vec3 cpos = soundTransform->GetLocalPosition() - *managed_channels[i].first;
		float sound = 100/ cpos.Length();
		if (sound >= 100)sound = 100;

		FMOD_VECTOR pos = { cpos.x, cpos.y, cpos.z };
		managed_channels[i].second->setVolume(sound);
		managed_channels[i].second->set3DAttributes(&pos,&vel);
	}
	for (int i = 0; i < managed_2Dchannels.size(); ++i) {
		bool isfin;
		managed_2Dchannels[i]->isPlaying(&isfin);
		if (!isfin) {
			auto it = managed_2Dchannels.begin() + i;
			managed_2Dchannels.erase(it);
			--i;
			continue;
		}
	}
	g_fmSystem->update();
}
