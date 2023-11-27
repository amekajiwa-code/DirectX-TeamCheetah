#include "pch.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Animation.h"

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
	{
		auto tex = make_shared<Texture>();
		tex->SetName(L"night");
		wstring path = RESOURCES_ADDR_TEXTURE;
		path += L"night.png";
		tex->CreateTexture(path);
		AddResource(tex->GetName(), tex);
	}
	{
		auto tex = make_shared<Texture>();
		tex->SetName(L"snake");
		wstring path = RESOURCES_ADDR_SPRITE;
		path += L"Snake.bmp";
		tex->CreateTexture(path);
		AddResource(tex->GetName(), tex);
	}

}

void ResourceManager::CreateDefaultMesh()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectagnle();
	AddResource(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	wstring path = RESOURCES_ADDR_SHADER;
	path += L"Default.hlsl";
	auto vertexShader = make_shared<VertexShader>(_device);
	vertexShader->CreateShader(path, "VS", "vs_5_0");

	auto inputLayout = make_shared<InputLayout>(_device);
	inputLayout->CreateInputLayout(VertexTextureData::descs, vertexShader->GetBlob());

	auto pixelShader = make_shared<PixelShader>(_device);
	pixelShader->CreateShader(path, "PS", "ps_5_0");

	//shader
	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"DefaultS");
	shader->SetVertexShader(vertexShader);
	shader->SetInputLayout(inputLayout);
	shader->SetPixelShader(pixelShader);
	AddResource(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"DefaultM");
	material->SetShader(GetResource<Shader>(L"DefaultS"));
	material->SetTexture(GetResource<Texture>(L"night"));
	AddResource(material->GetName(), material);
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
}
