#pragma once
#include "engine/IExecute.h"

#include "Character.h"
#include "Player.h"
#include "ClientPacketHandler.h"
#include "SpawnManager.h"
//Server
#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"

class Unit;


class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	//Shader
	shared_ptr<Shader>		_shader;
	shared_ptr<Shader> _terShader;
	//Character
	shared_ptr<Unit> _warrior;
	shared_ptr<Unit> _coreHound;
	//Map
	shared_ptr<GameObject>	_map;
	//client
	ClientServiceRef _service;
	float _threadTimer = 0.0f;
	SendBufferRef _sendBuffer;
	//test
	shared_ptr<Texture> _dissolve;
	bool _isdisv = false;
	//camera
	shared_ptr<GameObject> _childCamera;
};

