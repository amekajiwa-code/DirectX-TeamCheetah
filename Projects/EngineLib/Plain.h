#pragma once
#include "pch.h"

using Vector2 = Vec2;
using Vector3 = Vec3;
using Vector4 = Vec4;

using PlainVector = vector<VertexTextureNormalTangentData>;
using PlainPointerVector = vector<VertexTextureNormalTangentData*>;

struct Plaininfo {
	UINT col;
	UINT row;
	float distance;
	float heightScale;
	 std::wstring shaderFilePath;
	 std::wstring shaderFilename;
	 std::wstring textureFilePath;
	 std::wstring textureFilename;
	 std::wstring meshKey;
};

class Plain :public MonoBehaviour
{
private:
	shared_ptr<Shader> shader;
	shared_ptr<Texture> texture;
	shared_ptr<Material> material;
	Plaininfo plainDesc;

	UINT number_of_Verticles = 0;
	UINT number_of_Face = 0;
	UINT number_of_CellRows = 0;
	UINT number_of_CellCols = 0;
	UINT number_of_Cols = 0;
	UINT number_of_Rows = 0;

	float eachDistance = 0.0f;
	float heightScale = 0.0f;

public:
	Plain();
	virtual ~Plain();
public:
	shared_ptr<Shader> GetShader() {
		return shader;
	}
	void Set(Plaininfo& _plainDesc);
	inline Plaininfo GetPlainDesc() {
		return plainDesc;
	};
	virtual float GetHeightofVertex(UINT vertexIndex);
	virtual Vector3 GetNormalofVertex(UINT vertexIndex);
	virtual Vector4 GetColorOfVertex(UINT vertexindex);

	UINT GetCellRows() {
		return number_of_CellRows;
	};
	UINT GetCellCols() {
		return number_of_CellCols;
	}
	UINT GetRows() {
		return number_of_Rows;
	};
	UINT GetCols() {
		return number_of_Cols;
	}
	float GetEachDistance() {
		return eachDistance;
	};
	float GetHeightScale() {
		return heightScale;
	};

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

