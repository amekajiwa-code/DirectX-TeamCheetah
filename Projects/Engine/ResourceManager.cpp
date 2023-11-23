#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"

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
	auto tex = make_shared<Texture>();
	tex->SetName(L"night");
	wstring path = RESOURCES_ADDR_TEXTURE;
	tex->CreateTexture(L"night.png");
	AddResource(tex->GetName(), tex);
}

void ResourceManager::CreateDefaultMesh()
{
}

void ResourceManager::CreateDefaultShader()
{
}

void ResourceManager::CreateDefaultAnimation()
{
}

void ResourceManager::Init()
{
}
