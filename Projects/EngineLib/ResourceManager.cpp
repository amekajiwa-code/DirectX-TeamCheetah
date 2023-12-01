#include "pch.h"
#include "ResourceManager.h"
//#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
//#include "Material.h"
//#include "Animation.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager()
{
	_device = GRAPHICS()->GetDevice();
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::CreateDefaultTexture()
{
}

void ResourceManager::CreateDefaultMesh()
{
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
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}