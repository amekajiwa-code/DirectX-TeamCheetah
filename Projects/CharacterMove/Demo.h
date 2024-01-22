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

class Demo : public IExecute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	//Shader
	shared_ptr<Shader>		_shader;
	//Camera
	shared_ptr<GameObject>	_camera;
	//Character
	shared_ptr<GameObject>	_chr;
	//client
	ClientServiceRef service;
	float ThreadTimer = 0.0f;
	//Map
	shared_ptr<GameObject>	_map;
};

