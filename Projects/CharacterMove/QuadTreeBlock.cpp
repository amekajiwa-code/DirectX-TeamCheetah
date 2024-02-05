#include "pch.h"
#include "QuadTreeBlock.h"

void TerrainBlock::SetRoot(shared_ptr<Plain> refMap, int depth)
{
	BlockMeshKey = refMap->GetPlainDesc().meshKey;
	BlockTextureKey = refMap->GetPlainDesc().textureFilename;
	BlockShaderKey = refMap->GetPlainDesc().shaderFilename;
	shared_ptr<Mesh> terrain_Mesh = MANAGER_RESOURCES()->GetResource<Mesh>(BlockMeshKey);
	
	auto& mesh_VertexList = terrain_Mesh->GetGeo()->GetVertices();
	this->list_of_Verties.resize(mesh_VertexList.size());
	for (int i = 0; i < list_of_Verties.size(); i++) {
		list_of_Verties[i] = const_cast<VertexTextureNormalTangentData*>(&(mesh_VertexList[i]));
	}
	this->Included_Cols = refMap->GetCols();
	this->Included_Rows = refMap->GetRows();
	this->point_of_LeftTop = 0;
	this->point_of_RightTop = Included_Cols - 1;
	this->point_of_LeftBottom = Included_Rows * (Included_Cols - 1);
	this->point_of_RightBottom = (Included_Rows * Included_Cols) - 1;
	CountsOfDepths = 0;
	CreateBoundingBox(this);
	DivideBlock(depth, this);
//	this->GetMeshRenderer()->SetMesh(terrain_Mesh);
//	this->GetMeshRenderer()->SetMaterial(MANAGER_RESOURCES()->GetResource<Material>(BlockTextureKey));
}

void TerrainBlock::DivideBlock(int depth, TerrainBlock* parentBlock)
{
	int currentdepth = parentBlock->CountsOfDepths + 1;
	if (currentdepth > depth) {
		return;
	}
	parentBlock->isDivided = true;
	bool isOdd = (parentBlock->Included_Rows % 2 == 1 && parentBlock->Included_Cols % 2 == 1);
	UINT halfCols = parentBlock->Included_Cols / 2;
	UINT halfRows = parentBlock->Included_Rows / 2;
	if (isOdd % 2 == 1) {
		halfCols += 1;
		halfRows += 1;
	}
	for (int i = 0; i < 4; ++i) {
		parentBlock->childs[i] = std::make_shared<TerrainBlock>();
		parentBlock->childs[i]->parent = parentBlock;
		parentBlock->childs[i]->CountsOfDepths = currentdepth;
		if (isOdd) {
			parentBlock->childs[i]->Included_Cols = halfCols;
			parentBlock->childs[i]->Included_Rows = halfRows;
		}
		else {
			parentBlock->childs[i]->Included_Cols = halfCols + 1;
			parentBlock->childs[i]->Included_Rows = halfRows + 1;
		}
		parentBlock->childs[i]->list_of_Verties.reserve(parentBlock->list_of_Verties.size() / 4);
//		parentBlock->childs[i]->list_of_Height.reserve(parentBlock->list_of_Height.size() / 4);
		parentBlock->childs[i]->point_of_LeftTop = 0;
		parentBlock->childs[i]->point_of_RightTop = parentBlock->childs[i]->Included_Cols - 1;
		parentBlock->childs[i]->point_of_LeftBottom = parentBlock->childs[i]->Included_Rows * (parentBlock->childs[i]->Included_Cols - 1);
		parentBlock->childs[i]->point_of_RightBottom = (parentBlock->childs[i]->Included_Rows * parentBlock->childs[i]->Included_Cols) - 1;
//		parentBlock->childs[i]->Set(*(parentBlock->renderer.device), *(parentBlock->renderer.immediateContext), parentBlock->renderer.imagesfileKey, parentBlock->renderer.shaderKey);
	}
	if (isOdd) {
		for (int rowIndex = 0; rowIndex < parentBlock->Included_Rows; ++rowIndex) {
			for (int colindex = 0; colindex < parentBlock->Included_Cols; ++colindex) {
				int vertexIndex = (rowIndex * parentBlock->Included_Rows) + colindex;

				if (rowIndex < halfRows && colindex < halfCols) {
					parentBlock->childs[0]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//1
				if (rowIndex < halfRows && colindex >= halfCols - 1) {
					parentBlock->childs[1]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//2
				if (rowIndex >= halfRows - 1 && colindex < halfCols) {
					parentBlock->childs[2]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//3
				if (rowIndex >= halfRows - 1 && colindex >= halfCols - 1) {
					parentBlock->childs[3]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
			}
		}
	}
	else {
		for (int rowIndex = 0; rowIndex < parentBlock->Included_Rows; ++rowIndex) {
			for (int colindex = 0; colindex < parentBlock->Included_Cols; ++colindex) {
				int vertexIndex = (rowIndex * parentBlock->Included_Rows) + colindex;
				//0
				if (rowIndex < halfRows + 1 && colindex < halfCols + 1) {
					parentBlock->childs[0]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//1
				if (rowIndex < halfRows + 1 && colindex >= halfCols - 1) {
					parentBlock->childs[1]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//2
				if (rowIndex >= halfRows - 1 && colindex < halfCols + 1) {
					parentBlock->childs[2]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//3
				if (rowIndex >= halfRows - 1 && colindex >= halfCols - 1) {
					parentBlock->childs[3]->list_of_Verties.push_back(parentBlock->list_of_Verties[vertexIndex]);
				}
				//WTF?
			}
		}

	}

	for (int i = 0; i < 4; ++i) {
		parentBlock->childs[i]->CreateBoundingBox(parentBlock->childs[i].get());
		int sizes = parentBlock->childs[i]->list_of_Verties.size();
		shared_ptr<Mesh> childMesh = make_shared<Mesh>();
		shared_ptr<Geometry<VertexTextureNormalTangentData>> childGeo = make_shared<Geometry<VertexTextureNormalTangentData>>();
		parentBlock->childs[i]->childVerties.resize(sizes);

		for (int j = 0; j < parentBlock->childs[i]->list_of_Verties.size(); ++j) {
			parentBlock->childs[i]->childVerties[j] = *(parentBlock->childs[i]->list_of_Verties[j]);
		}

		parentBlock->childs[i]->childIndies.reserve(((parentBlock->childs[i]->Included_Cols - 1) * (parentBlock->childs[i]->Included_Rows - 1)) * 6);

		int currentIndex = 0;
		for (int row = 0; row < (parentBlock->childs[i]->Included_Rows - 1); ++row) {
			for (int col = 0; col < (parentBlock->childs[i]->Included_Cols - 1); ++col) {
				int nextRow = row + 1;
				int nextCol = col + 1;

				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row + 1) + (col));
				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row)+(col + 1));
				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row)+(col));
				//  [1] - [2]
				//   	\  |
				//		  [0]
				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row)+(col + 1));
				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row + 1) + (col));
				parentBlock->childs[i]->childIndies.push_back((parentBlock->childs[i]->Included_Cols) * (row + 1) + (col + 1));

			}
		}
		childGeo->SetVertices(parentBlock->childs[i]->childVerties);
		childGeo->SetIndices(parentBlock->childs[i]->childIndies);
		childMesh->SetGeoMetryAndCreateBuffer(childGeo);
		parentBlock->childs[i]->BlockMeshKey = ((wstring)QUADTERRAIN_MESHKEY)+to_wstring(++meshKeyCoutner);
		parentBlock->childs[i]->BlockTextureKey = parentBlock->BlockTextureKey;
		parentBlock->childs[i]->BlockShaderKey = parentBlock->BlockShaderKey;
		MANAGER_RESOURCES()->AddResource(parentBlock->childs[i]->BlockMeshKey,childMesh);
		parentBlock->childs[i]->personal_Mesh = childMesh;
		parentBlock->childs[i]->Awake();
		shared_ptr<MeshRenderer> childRenderer = make_shared<MeshRenderer>();
		parentBlock->childs[i]->AddComponent(childRenderer);
		parentBlock->childs[i]->DivideBlock(depth, parentBlock->childs[i].get());
	}

	return;
}

Vec2 TerrainBlock::GetHeightFromBlock(TerrainBlock* block)
{
	//x=top,y=bottom;
	Vec2 heigths(0, 0);
	int sizeofheight = block->list_of_Verties.size();
	for (int index = 0; index < sizeofheight; ++index) {

		if (heigths.x < (block->list_of_Verties[index]->position.y))
		{
			heigths.x = (block->list_of_Verties[index]->position.y);
			continue;
		}
		if (heigths.y > (block->list_of_Verties[index]->position.y))
		{
			heigths.y = (block->list_of_Verties[index]->position.y);
		}
	}
	return heigths;
}

void TerrainBlock::CreateBoundingBox(TerrainBlock* block)
{
	//TODO 
	/* Vector3 Pos에 영항받게 바꿔야함*/
	UINT min_point = block->point_of_LeftTop;
	UINT max_point = block->point_of_RightBottom;
	Vec2 height = GetHeightFromBlock(block);
	block->terrainCube.min.x = block->list_of_Verties[min_point]->position.x;
	block->terrainCube.min.y = height.y;
	block->terrainCube.min.z = block->list_of_Verties[min_point]->position.z;

	block->terrainCube.max.x = block->list_of_Verties[max_point]->position.x;
	block->terrainCube.max.y = height.x;
	block->terrainCube.max.z = block->list_of_Verties[max_point]->position.z;

	//For OBB 
	block->terrainCube.axis[0] = { 1,0,0 };
	block->terrainCube.axis[1] = { 0,1,0 };
	block->terrainCube.axis[2] = { 0,0,1 };

	block->terrainCube.center = (block->terrainCube.max + block->terrainCube.min) * 0.5f;

	block->terrainCube.extent[0] = block->terrainCube.max.x - block->terrainCube.center.x;
	block->terrainCube.extent[1] = block->terrainCube.max.y - block->terrainCube.center.y;
	block->terrainCube.extent[2] = block->terrainCube.max.z - block->terrainCube.center.z;

}

void TerrainBlock::Start()
{
	auto renderer = GetMeshRenderer();
	if (renderer) {
		//renderer->SetMesh(personal_Mesh);
		renderer->SetMesh(MANAGER_RESOURCES()->GetResource<Mesh>(BlockMeshKey));
		renderer->SetMaterial(MANAGER_RESOURCES()->GetResource<Material>(BlockTextureKey)->Clone());
		renderer->SetPass(0);
	}
	else {
#ifdef _DEBUG
		MessageBoxA(NULL, "WTF THIS MASSAGE FROM Plain AWAKE", "ERROR FROM PLAIN", MB_OK);
		assert(true);
#endif // _DEBUG

	}
	GameObject::Start();
}

void TerrainBlock::Update()
{
	
	GameObject::Update();
}


bool QuadTreeTerrain::Start()
{
	for (auto c : allLeafBlocks) {
		c->Start();
	}

	return true;
}

bool QuadTreeTerrain::Frame(FrustumBox& Frustom)
{
	renderBlocks.clear();

	for (int i = 0; i < allLeafBlocks.size(); ++i) {
		allLeafBlocks[i]->Update();
		if (Frustom.CheckOBBInPlane(allLeafBlocks[i]->GetTerrain_Cube())) {
			renderBlocks.push_back(allLeafBlocks[i]);

			//for (int j = 0; j < allLeafBlocks[i]->renderer.vertexList.size(); ++j) {
			//	auto& a=allLeafBlocks[i]->GetList_of_Vertex();
			//	allLeafBlocks[i]->renderer.vertexList[j] = *(a[j]);
			//}
		}
	}

	if (renderBlocks.empty()) {
		return false;
	}
	return true;
}

bool QuadTreeTerrain::PreUpdate(int index)
{
	for (int i = 0; i < renderBlocks.size(); i++) {
		//renderBlocks[i]->SetMatrix(matWorld, matView, matProj);
		//renderBlocks[i]->Render();
	}
	return true;;
}

void QuadTreeTerrain::Update()
{
//	ComPtr<ID3DX11EffectShaderResourceVariable> shadow;
//	//(MANAGER_RESOURCES()->GetResource<Shader>(root_Block->BlockShaderKey))->;
//	Vec4 vClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	//vector<Matrix> ShadowMatList;
//	Matrix shadowMat;
////	ShadowMatList.resize(renderBlocks.size());
//	if (rt.Begin(GRAPHICS()->GetDeviceContext().Get(), vClearColor))
//	{
//		
//			auto renderer = terrain->GetMeshRenderer();
//			renderer->SetPass(1);
//			shadowMat = renderer->ShadowUpdate();
//		
//		rt.End(GRAPHICS()->GetDeviceContext().Get());
//	}
	for (int i = 0; i < renderBlocks.size(); i++) {

		auto renderer= renderBlocks[i]->GetMeshRenderer();
		renderer->SetPass(0);
		
		if(splatter)splatter->PreUpdate();
		auto _mat = MANAGER_RESOURCES()->GetResource<Material>(renderBlocks[i]->GetTextureKey());
//		_mat->GetDiffuseMap()->SetDubugTexture(rt.GetDsvSRV());
		auto _shader = _mat->GetShader();
//		ShadowDesc shadowdesc;
		MANAGER_SHADOW()::GetInstance();
		//shadowdesc.mat = shadowMat;
		//_shader->PushShadowData(shadowdesc);
		//shadow = _shader->GetSRV("DepthMap");
		//shadow->SetResource(rt.GetDsvSRV());

		renderer->LegacyUpdate();
	}
	return;

}

bool QuadTreeTerrain::PostUpdate(int index)
{
	for (int i = 0; i < renderBlocks.size(); i++) {
		//renderBlocks[i]->SetMatrix(matWorld, matView, matProj);
		//renderBlocks[i]->Render();
	}
	return true;;
}
