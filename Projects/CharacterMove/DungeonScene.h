#pragma once
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

class Unit;

class DungeonScene : public Scene
{
	//Map
	shared_ptr<FrustomCamera> frustom;
	//Spawn Pos
	Vec3 spawnPos = Vec3(-374, 25, 338);
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
	float _threadTimer = 0.0f;
	SendBufferRef _sendBuffer;
	Player_INFO sendInfo; //플레이어 인포
	int latestMessageSize = 0;
	//test
	shared_ptr<Texture> _dissolve;
	bool _isdisv = false;
	//camera
	shared_ptr<GameObject> _childCamera;

	//Camera
	shared_ptr<GameObject> _camera;
public:
	virtual void Init();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
};


