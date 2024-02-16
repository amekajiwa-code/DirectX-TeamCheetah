#pragma once
//#include "Character.h"
//#include "Player.h"
//#include "ClientPacketHandler.h"
//#include "SpawnManager.h"

#include "engine\\FrustomCamera.h"
#include "QuadTreeBlock.h"
#include "Skybox.h"

#include "Character.h"
#include "Player.h"
#include "ClientPacketHandler.h"
#include "SpawnManager.h"
//Server
#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"
//UI
#include "UI_MANAGER.h"

class Unit;

class BaseScene : public Scene
{
	//Map
	shared_ptr<FrustomCamera> frustom;
	//obj
	shared_ptr<Terrain> _terrain;
	shared_ptr<QuadTreeTerrain> quadTreeTerrain;
	shared_ptr<LayerSplatter> splatter;
	shared_ptr<Skybox> skyBox;

	//Shader
	shared_ptr<Shader>	_shader;
	shared_ptr<Shader> _terShader;
	//Character
	shared_ptr<Unit> _warrior;
	shared_ptr<Unit> _coreHound;
	//client
	ClientServiceRef _service;
	float _threadTimer = 0.0f;
	SendBufferRef _sendBuffer;
	//test
	shared_ptr<Texture> _dissolve;
	bool _isdisv = false;
	//camera
	shared_ptr<GameObject> _childCamera;
	
	//Camera
	shared_ptr<GameObject> _camera;
	//임시공격
	bool _isAttack = false;
	float _attackTimer = 0.0f;
public:
	virtual void Init();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
};

