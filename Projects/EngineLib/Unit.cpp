#include "pch.h"
#include "Unit.h"
#include "BaseCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

void Unit::AddAnimation(const shared_ptr<Model>& com, wstring animOwner, wstring animName)
{
	wstring addr = RESOURCES_ADDR_ANIMATION;
	addr += animOwner;
	addr += L"/";
	addr += animName;
	addr += L".anim";

	com->ReadAnimation(addr);
}

void Unit::AddModelAndMaterial(const shared_ptr<Model>& com, wstring name)
{
	wstring MeshAdr = RESOURCES_ADDR_MESH_SKELETAL;
	MeshAdr += name;
	MeshAdr += L"/";
	MeshAdr += name;
	MeshAdr += L".mesh";

	wstring MaterialAdr = RESOURCES_ADDR_TEXTURE_SKELETAL;
	MaterialAdr += name;
	MaterialAdr += L"/";
	MaterialAdr += name;
	MaterialAdr += L".xml";

	com->ReadModel(MeshAdr);
	com->ReadMaterial(MaterialAdr);
}

void Unit::Awake()
{
	Super::Awake();
}

void Unit::Start()
{
	Super::Start();
}

void Unit::FixedUpdate()
{
	Super::FixedUpdate();
}

void Unit::Update()
{
	Super::Update();
}

void Unit::LateUpdate()
{
	Super::LateUpdate();
}
