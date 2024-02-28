#pragma once
struct DamageIndiCatorBox {
	int damage;
	float textDuration;
	Vec3 pos;
public:
	DamageIndiCatorBox() {};
	DamageIndiCatorBox(int _damage, float _duration, Vec3 _Pos) :
		damage(_damage), textDuration(_duration), pos(_Pos) {
	};

	void Set(int _damage, float _duration, Vec3 _pos) {
		damage = _damage;
		textDuration = _duration;
		pos = _pos;

	};

};
struct IndicatorInstance {
	Matrix world;
	UINT num;
};

class DamageIndicator
{
	shared_ptr<VertexBuffer> instanceBuffer;
	vector<IndicatorInstance> renderList;
	list<DamageIndiCatorBox> managingBoxList;
	shared_ptr<GameObject> cam;

	vector<ID3D11ShaderResourceView*> numSRVs;
	ComPtr<ID3DX11EffectShaderResourceVariable> numArray;

	shared_ptr<Mesh> _mesh;
	shared_ptr<Shader> _shader;
	float xScale = 2;
	float yScale = 3;

public:

	static	DamageIndicator& GetInstance();
	void Init();
	void SetCamera(shared_ptr<GameObject> obj) {
		cam = obj;
	};
	void Frame();
	void Render();
	void Add(DamageIndiCatorBox IndicatorDesc) {
		managingBoxList.push_back(IndicatorDesc);
	};
	void Clear() {
		managingBoxList.clear();
	}
private:
	DamageIndicator();
private:
	void CreateInstance();
	void CreateMesh();
public:
	~DamageIndicator();
};

