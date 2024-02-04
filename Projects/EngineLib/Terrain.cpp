#include "pch.h"
#include "Terrain.h"
#include "Plain.h"
Terrain::Terrain(HeightPlainInfo HeightDesc){
	this->plainHeightAddr = make_shared<PlainHeightAdder>();
	plain=plainHeightAddr->Set(HeightDesc);

	_scripts.push_back(plain);
}

shared_ptr<Plain> Terrain::GetPlain()
{
	return plain;
}

float Terrain::GetHeight(float posX,float posZ)
{

	UINT cols = plainHeightAddr->GetHeightInfo().col;
	UINT rows = plainHeightAddr->GetHeightInfo().row;
	UINT cellCols = cols - 1;
	UINT cellRows = rows - 1;
	float distance = plainHeightAddr->GetHeightInfo().distance;
	float cellX = (float)(cellCols * distance / 2.0f + posX);
	float cellZ = (float)(cellRows * distance / 2.0f - posZ);

	cellX /= (float)distance;
	cellZ /= (float)distance;

	float vertexCol = std::floorf(cellX);
	float vertexRow = std::floorf(cellZ);

	if (vertexCol < 0.0f) vertexCol = 0.0f;
	if (vertexRow < 0.0f) vertexRow = 0.0f;
	if ((float)(cols - 2) < vertexCol)	vertexCol = (float)(cols - 2);
	if ((float)(rows - 2) < vertexRow)	vertexRow = (float)(rows - 2);


	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = plainHeightAddr->GetHeightFromList((int)vertexRow, (int)vertexCol);
	float B = plainHeightAddr->GetHeightFromList((int)vertexRow, (int)vertexCol + 1);
	float C = plainHeightAddr->GetHeightFromList((int)vertexRow + 1, (int)vertexCol);
	float D = plainHeightAddr->GetHeightFromList((int)vertexRow + 1, (int)vertexCol + 1);


	float deltaX = cellX - vertexCol;
	float deltaZ = cellZ - vertexRow;
	// 보간작업를 위한 기준 페잇스를 찾는다. 
	float heights = 0.0f;
	// 윗페이스를 기준으로 보간한다.
	// fDeltaZ + fDeltaX < 1.0f
	if (deltaZ < (1.0f - deltaX))  //ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C	
		// 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다.		
		heights = A + Lerp(0.0f, uy, deltaX) + Lerp(0.0f, vy, deltaZ);
	}
	// 아래페이스를 기준으로 보간한다.
	else // DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B
		// 두 정점의 높이값의 차이를 비교하여 델타Z의 값에 따라 보간값을 찾는다.		
		heights = D + Lerp(0.0f, uy, 1.0f - deltaX) + Lerp(0.0f, vy, 1.0f - deltaZ);
	}
	return heights;
}

void Terrain::Start()
{

	auto renderer =GetMeshRenderer();
	if (renderer) {
		const wstring meshKey = plain->GetPlainDesc().meshKey;
		const wstring materialkey = plain->GetPlainDesc().textureFilename;
		renderer->SetMesh(MANAGER_RESOURCES()->GetResource<Mesh>(meshKey));
		renderer->SetMaterial(MANAGER_RESOURCES()->GetResource<Material>(materialkey));
	}
	else {
#ifdef _DEBUG
		MessageBoxA(NULL, "WTF THIS MASSAGE FROM Plain AWAKE", "ERROR FROM PLAIN", MB_OK);
		assert(true);
#endif // _DEBUG

	}
	GameObject::Start();
}

void Terrain::Update()
{
	GameObject::Update();
}
