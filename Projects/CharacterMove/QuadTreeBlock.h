#pragma once
#include "engine\FrustomCamera.h"
#include "LayerSplatter.h"
#define QUADTERRAIN_MESHKEY L"QuadTreeTrerrainedKey"
#include "engine\RenderTarget.h"
static int meshKeyCoutner=0;

class TerrainBlock : public GameObject {
	Terrain_Cube terrainCube;
	int CountsOfDepths = 0;
	wstring BlockMeshKey=L"";
	vector< VertexTextureNormalTangentData> childVerties;
	vector<uint32> childIndies;

	//UINT Included_CellRows;
	//UINT Included_CellCols;
	UINT Included_Rows;
	UINT Included_Cols;

	//std::vector<DWORD*> list_of_Indies;
	PlainPointerVector list_of_Verties;
//	std::vector<float*> list_of_Height;

public:
	wstring BlockTextureKey = L"";
	wstring BlockShaderKey = L"";
	TerrainBlock* parent = nullptr;
	UINT point_of_LeftTop=0;
	UINT point_of_LeftBottom=0;
	UINT point_of_RightTop=0;
	UINT point_of_RightBottom=0;
	UCHAR lod_offset=NULL; // 8,4,2,1 ==Limit==15; 
	UCHAR lod_level=NULL;
	shared_ptr<Mesh> personal_Mesh;
	bool isDivided = false;
	std::array<shared_ptr<TerrainBlock>, 4> childs{ nullptr, };
	std::array<shared_ptr<TerrainBlock>,  4> neighbor{ nullptr, };// 0=top,1=left,2=right,3=down;
public:
	//inline std::vector<DWORD*>& GetList_of_Indies() {
	//	return list_of_Indies;
	//};
	inline const wstring& GetMeshKey() {
		return BlockMeshKey;
	};
	inline const wstring& GetTextureKey() {
		return BlockTextureKey;
	};
	inline PlainPointerVector &GetList_of_Vertex() {
		return list_of_Verties;
	};
	//inline std::vector<float*>& GetList_of_Height() {
	//	return list_of_Height;
	//};
	inline Terrain_Cube& GetTerrain_Cube() {
		return terrainCube;
	}
	inline UINT& GetIncluded_Cols() {
		return Included_Cols;
	}
	inline UINT& GetIncluded_Rows() {
		return Included_Rows;
	}
public:
	void SetRoot(shared_ptr<Plain> refMap, int depth);
public:
	TerrainBlock() {};
	~TerrainBlock() {};
public:
	void DivideBlock(int depth, TerrainBlock* Parent);
	Vec2 GetHeightFromBlock(TerrainBlock* block);
	void CreateBoundingBox(TerrainBlock* block);
public:
	virtual void Start() override;
	virtual void Update() override;
};

class QuadTreeTerrain
{
	shared_ptr<LayerSplatter> splatter=nullptr;
	shared_ptr<TerrainBlock> root_Block;
	shared_ptr<Terrain> terrain;
	RenderTarget rt;
public:

	std::vector<shared_ptr<TerrainBlock>> allLeafBlocks;
	std::vector<shared_ptr<TerrainBlock>> renderBlocks;

public:
	QuadTreeTerrain(){};

	void Set(shared_ptr<Terrain> refPlain, int depth){
		terrain = refPlain;
		root_Block = std::make_shared<TerrainBlock>();
		root_Block->SetRoot(refPlain->GetPlain(), depth);

		AddBlocks(root_Block);
	}
	void AddSplatter(shared_ptr<LayerSplatter> _splatter) { splatter = _splatter; };
	void AddBlocks(shared_ptr<TerrainBlock>block) {
		if (block->isDivided) {
			for (int i = 0; i < 4; i++) {
				AddBlocks(block->childs[i]);
			}
		}
		else {
			allLeafBlocks.push_back(block);
		}
		return;
	};
	~QuadTreeTerrain() {};

public:
	bool Start();
	bool Frame(FrustumBox& Frustom);
	int	 GetRenderBlockCount() {
		return renderBlocks.size();
	};
	bool PreUpdate(int index);
	void Update();
	bool PostUpdate(int index);




public:

};

