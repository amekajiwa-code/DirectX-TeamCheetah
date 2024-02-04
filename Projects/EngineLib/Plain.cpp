#include "pch.h"
#include "Plain.h"

Plain::Plain()
{
}

Plain::~Plain()
{
}

void Plain::Set(Plaininfo& _plainDesc)
{
	plainDesc = _plainDesc;

	if (number_of_Cols == 0) {
		number_of_Cols = plainDesc.col;
	}
	if (number_of_Rows == 0) {
		number_of_Rows = plainDesc.row;
	}
	float halfCols = (number_of_Cols - 1) * 0.5;
	float halfRows = (number_of_Rows - 1) * 0.5;
	number_of_CellCols = number_of_Cols - 1;
	number_of_CellRows = number_of_Rows - 1;
	number_of_Face = (number_of_CellRows * number_of_CellCols) * 2;
	eachDistance = plainDesc.distance;
	heightScale = plainDesc.heightScale;

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->CreateGridWithDistance(plainDesc.row, plainDesc.col,plainDesc.distance);
	MANAGER_RESOURCES()->AddResource(plainDesc.meshKey, mesh);

	texture=MANAGER_RESOURCES()->LoadResource<Texture>(plainDesc.textureFilename, plainDesc.textureFilePath);
	MANAGER_RESOURCES()->AddResource<Texture>(plainDesc.textureFilename,texture);
	MANAGER_RESOURCES()->AddResource(plainDesc.shaderFilename, make_shared<Shader>(plainDesc.shaderFilePath));
	shader = MANAGER_RESOURCES()->GetResource<Shader>(plainDesc.shaderFilename);

	
	//생성
	shared_ptr<Material> material = make_shared<Material>();
	{
		//쉐이더 설정
		//auto shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		material->SetShader(shader);
		//텍스쳐 설정
		auto tex = MANAGER_RESOURCES()->GetResource<Texture>(plainDesc.textureFilename);
		material->SetDiffuseMap(tex);
		//노멀맵 텍스쳐 설정
		auto normal = MANAGER_RESOURCES()->GetResource <Texture> (L"DefaultNormal");
		material->SetNormalMap(normal);
		auto spec = MANAGER_RESOURCES()->GetResource <Texture>(L"DefaultSpecular");
		material->SetSpecularMap(spec);
	}
	MANAGER_RESOURCES()->AddResource<Material>(plainDesc.textureFilename,material);
	//Desc
	
}

float Plain::GetHeightofVertex(UINT vertexIndex)
{
	return 0.0f;
}

Vector3 Plain::GetNormalofVertex(UINT vertexIndex)
{
	return Vector3(0,1,0);
}

Vector4 Plain::GetColorOfVertex(UINT vertexindex)
{
	return Vector4(1,1,1,1);
}


void Plain::Awake()
{
}

void Plain::Start()
{
}

void Plain::FixedUpdate()
{
}

void Plain::Update()
{
}

void Plain::LateUpdate()
{
}