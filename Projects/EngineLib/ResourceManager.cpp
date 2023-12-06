#include "pch.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::CreateDefaultTexture()
{
}

void ResourceManager::CreateDefaultMesh()
{
	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->CreateQuad();
		AddResource(L"Quad", mesh);
	}
	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->CreateCube();
		AddResource(L"Cube", mesh);
	}
	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->CreateSphere();
		AddResource(L"Sphere", mesh);
	}
}

void ResourceManager::CreateDefaultShader()
{
}

void ResourceManager::CreateDefaultMaterial()
{
}

void ResourceManager::CreateDefaultAnimation()
{
}

void ResourceManager::Init()
{
	//CreateDefaultTexture();
	CreateDefaultMesh();
	//CreateDefaultShader();
	//CreateDefaultMaterial();
	//CreateDefaultAnimation();
}
