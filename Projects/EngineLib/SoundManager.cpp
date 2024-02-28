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
	if (g_fmSystem == nullptr) {
		FMOD::System_Create(&g_fmSystem);
		g_fmSystem->init(128, FMOD_INIT_NORMAL, nullptr);
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
		_3DsoundDesc.velocity.x = 1.0f;
		_3DsoundDesc.velocity.y = 1.0f;
		_3DsoundDesc.velocity.z = 1.0f;
		g_fmSystem->set3DListenerAttributes(1, &_3DsoundDesc.position, &_3DsoundDesc.velocity, &_3DsoundDesc.forward, &_3DsoundDesc.up);
	}
	g_fmSystem->update();

}
