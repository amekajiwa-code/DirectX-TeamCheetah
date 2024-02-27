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
	float xScale = 4;
	float yScale = 6;
public:

	static	DamageIndicator& GetInstance() {
		static DamageIndicator indiCator;
		return indiCator;
	}

	void Init() {

		//Need To Change
		if (_shader == nullptr) {
			_shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Damage");
			if (_shader == nullptr) {
				_shader = make_shared<Shader>(L"Damage.fx");
				MANAGER_RESOURCES()->AddResource(L"Damage", _shader);
				numArray = _shader->GetSRV("NumListMap");
			}
			

			instanceBuffer = make_shared<VertexBuffer>();

			vector<IndicatorInstance> temp(500);
			instanceBuffer->CreateVertexBuffer(temp, /*slot*/1, /*cpuWrite*/true);

			_mesh = make_shared<Mesh>();

			vector<VertexTextureNormalTangentData> vtx;
			vtx.resize(4);

			vtx[0].position = Vec3(-xScale/ 2.f, -yScale/2.f, 0.f);
			vtx[1].position = Vec3(-xScale /2.f, yScale / 2.f, 0.f);
			vtx[2].position = Vec3(xScale / 2.f, -yScale / 2.f, 0.f);
			vtx[3].position = Vec3(xScale / 2.f, yScale / 2.f, 0.f);

			
			vtx[0].uv = Vec2(0.f, 0.875f);
			vtx[0].normal = Vec3(0.f, 0.f, -1.f);
			vtx[0].tangent = Vec3(1.0f, 0.0f, 0.0f);
			vtx[1].uv = Vec2(0.f, 0.f);
			vtx[1].normal = Vec3(0.f, 0.f, -1.f);
			vtx[1].tangent = Vec3(1.0f, 0.0f, 0.0f);
			vtx[2].uv = Vec2(0.6875f, 0.875f);
			vtx[2].normal = Vec3(0.f, 0.f, -1.f);
			vtx[2].tangent = Vec3(1.0f, 0.0f, 0.0f);
			vtx[3].uv = Vec2(0.6875f, 0.f);
			vtx[3].normal = Vec3(0.f, 0.f, -1.f);
			vtx[3].tangent = Vec3(1.0f, 0.0f, 0.0f);
			shared_ptr<Geometry<VertexTextureNormalTangentData>> _geo = make_shared<Geometry<VertexTextureNormalTangentData>>();
			_geo->SetVertices(vtx);

			vector<uint32> idx = { 0, 1, 2, 2, 1, 3 };
			_geo->SetIndices(idx);
			_mesh->SetGeoMetryAndCreateBuffer(_geo);
			for (int i = 0; i < 10; ++i) {
				std::wstring string = L"../../Resources/Font/num/";
				string += std::to_wstring(i);
				string += L".png";

				shared_ptr<Texture> tex = MANAGER_RESOURCES()->GetOrAddTexture(L"num" + to_wstring(i), string);
				numSRVs.push_back(tex->GetTexture().Get());
			}

		}
	};
	void SetCamera(shared_ptr<GameObject> obj) {
		cam = obj;
	};
	void Frame() {
		float time = MANAGER_TIME()->GetDeltaTime();
		for (auto it = managingBoxList.begin(); it != managingBoxList.end();) {
			if ((it)->textDuration <= 0.0f) {
				it = managingBoxList.erase(it);
				continue;
			}
			(it)->textDuration -= time;
			if ((it)->textDuration <= 0) {
				it = managingBoxList.erase(it);
				continue;
			}
			(it)->pos.y += 50.0f * time;

			std::vector<int> dividingDamage;

			if ((it)->damage >= 10) {
				int tempdamage = (it)->damage;
				int split = 10;
				while (true) {
					int splitednum = tempdamage % split;

					if (splitednum != 0) {
						splitednum /= (split / 10);
					}
					split *= 10;
					dividingDamage.push_back(splitednum);
					if (tempdamage * 10 < split) {
						break;
					}
				}
			}
			else {

				dividingDamage.push_back((it)->damage);
			}
			if (dividingDamage.size() % 2 == 0) {

				for (int i = dividingDamage.size() - 1; i >= 0; --i) {
					//for (int i = 0; i < dividingDamage.size(); ++i) {
					Vec3 numPos;
					numPos.x = (it)->pos.x + (-(xScale) * (dividingDamage.size()) + ((xScale * 2) * (dividingDamage.size() - i)));
					numPos.y = (it)->pos.y;
					numPos.z = (it)->pos.z;

					IndicatorInstance data;
					data.num = dividingDamage[i];
					auto look = (cam->GetTransform()->GetLookVector());
//					Vec3 look(1.0, 0, 0);
//					data.world = Matrix::CreateBillboard(numPos, cam->GetTransform()->GetLocalPosition(),
//						cam->GetTransform()->GetUpVector(), &look);
					data.world = Matrix::CreateBillboard(numPos, cam->GetTransform()->GetLocalPosition(),
						Vec3(1,0,0), &look);
					//TODO
					renderList.push_back(data);
				}

			}
			else {
				for (int i = dividingDamage.size() - 1; i >= 0; --i) {
					//for (int i =0  ; i < dividingDamage.size() ; ++i) {
					//TODO
					Vec3 numPos;
					numPos.x = (it)->pos.x + ((-(xScale) * (dividingDamage.size()) - (xScale / 2)) + ((xScale * 2) * (dividingDamage.size() - i)));
					numPos.y = (it)->pos.y;
					numPos.z = (it)->pos.z;

					IndicatorInstance data;
					data.num = dividingDamage[i];
					auto look = (cam->GetTransform()->GetLookVector());
//					Vec3 look(0, 1, 0);
					Matrix billmat =cam->GetTransform()->GetWorldMatrix();
					Vec3 dePos=numPos;
					dePos.x -= (it)->pos.x;
					Vec3 deScale;
					Quaternion deRot;
					billmat.Decompose(deScale,deRot,dePos);
					
//					data.world = billmat;
					Matrix detransmat = Matrix::CreateTranslation(dePos);
					Matrix rotate = Matrix::CreateFromQuaternion(deRot);
					Matrix transmat = Matrix::CreateTranslation(numPos);
					data.world *= rotate;
					data.world *= transmat;
//					data.world = Matrix::CreateBillboard(numPos, -cam->GetTransform()->GetLocalPosition());
//					Vec3(1,0,0), &look);
					//TODO
					renderList.push_back(data);
				}
			}
			++it;
		}

	};
	void Render() {
		numArray->SetResourceArray(&numSRVs.at(0), 0, 10);
		_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);


		D3D11_MAPPED_SUBRESOURCE subResource;
		DC()->Map(instanceBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		{
			::memcpy(subResource.pData, renderList.data(), sizeof(IndicatorInstance) * renderList.size());
		}
		DC()->Unmap(instanceBuffer->GetBuffer().Get(), 0);

		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();
		instanceBuffer->PushData();

		_shader->DrawIndexedInstanced(0, 0, _mesh->GetIndexBuffer()->GetCount(), instanceBuffer->GetCount());
		renderList.clear();
	};
	void Add(DamageIndiCatorBox IndicatorDesc) {
		managingBoxList.push_back(IndicatorDesc);

		//const uint32 dataCount = GetCount();
		//if (dataCount > _maxCount)
		//	CreateBuffer(dataCount);

		//_instanceBuffer->PushData();
		//_maxCount = maxCount;
		//_instanceBuffer = make_shared<VertexBuffer>();

		//vector<InstancingData> temp(maxCount);
		//_instanceBuffer->CreateVertexBuffer(temp, /*slot*/1, /*cpuWrite*/true);

	};
	void Clear() {
		managingBoxList.clear();
	}
private:
	DamageIndicator() {
	};
public:
	~DamageIndicator() {
	};
};

