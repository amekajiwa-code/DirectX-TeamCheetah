#include "pch.h"
#include "Sounds.h"

FMOD::System* g_fmSystem;

Sound::Sound() :Super(ResourceType::Sound)
{
}

Sound::~Sound()
{	
	if (fm_Sound)fm_Sound->release();
}

void Sound::Load(const wstring& path)
{
	if (g_fmSystem == nullptr) {
		FMOD::System_Create(&g_fmSystem);
		g_fmSystem->init(128, FMOD_INIT_NORMAL, 0);

	}
	string multipath;
	multipath.assign(path.begin(),path.end());
	FMOD_RESULT result = g_fmSystem->createSound(multipath.c_str(), FMOD_DEFAULT, nullptr, &fm_Sound);
	if (result != FMOD_OK) {
		assert("ERROR FROM SOUNDCLASS FMOD");
	}

}
FMOD::Channel* Sound::Play(bool doLoop)
{
	FMOD::Channel* channel;

	(doLoop) ? fm_Sound->setMode(FMOD_LOOP_NORMAL) : fm_Sound->setMode(FMOD_LOOP_OFF);
	fm_Sound->setMode(FMOD_2D);
	g_fmSystem->playSound(fm_Sound, nullptr, false, &channel);

	return channel;
}
FMOD::Channel* Sound::Play3D(bool doLoop, Vec3 pos, Vec3 vel = { 1,1,1 })
{
	FMOD::Channel* channel;

	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	velocity.x = vel.x;
	velocity.y = vel.y;
	velocity.z = vel.z;


	(doLoop) ? fm_Sound->setMode(FMOD_LOOP_NORMAL) : fm_Sound->setMode(FMOD_LOOP_OFF);
	fm_Sound->setMode(FMOD_3D);
	g_fmSystem->playSound(fm_Sound, nullptr, false, &channel);
	channel->set3DAttributes(&position, &velocity);

	return channel;
}
void Sound::PlayEffect()
{
	FMOD::Channel* channel;
	fm_Sound->setMode(FMOD_2D);
	g_fmSystem->playSound(fm_Sound, nullptr, false, &channel);

}
void Sound::Play3DEffect(Vec3 pos,Vec3 vel = { 1,1,1 })
{
	FMOD::Channel* channel;

	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	velocity.x = vel.x;
	velocity.y = vel.y;
	velocity.z = vel.z;
	fm_Sound->setMode(FMOD_3D);

	g_fmSystem->playSound(fm_Sound, nullptr, false, &channel);
	channel->set3DAttributes(&position, &velocity);

}

//(Vec3 pos, Vec3 up, Vec3 forward, Vec3 velocity = { 1,1,1 })
//{
//	FMOD_3D_ATTRIBUTES _3DsoundDesc;
//	_3DsoundDesc.position.x = pos.x;
//	_3DsoundDesc.position.y = pos.y;
//	_3DsoundDesc.position.z = pos.z;
//	_3DsoundDesc.up.x = up.x;
//	_3DsoundDesc.up.y = up.y;
//	_3DsoundDesc.up.z = up.z;
//	_3DsoundDesc.forward.x = forward.x;
//	_3DsoundDesc.forward.y = forward.y;
//	_3DsoundDesc.forward.z = forward.z;
//	_3DsoundDesc.velocity.x = velocity.x;
//	_3DsoundDesc.velocity.y = velocity.y;
//	_3DsoundDesc.velocity.z = velocity.z;