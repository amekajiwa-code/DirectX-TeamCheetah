#pragma once
struct DamageIndiCatorBox {
	int damage;
	float textDuration;
	Vec3* pos;
public:
	DamageIndiCatorBox() {};
	DamageIndiCatorBox(int _damage, float _duration, Vec3* _Pos) :
		damage(_damage), textDuration(_duration), pos(_Pos) {
	};

	void Set(int _damage, float _duration, Vec3* _pos) {
		damage = _damage;
		textDuration = _duration;
		pos = _pos;

	};

};
class DamageIndicator
{
public:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
public:
	list<DamageIndiCatorBox*> managingBoxList;
	vector<shared_ptr<Material>> numberList;
	vector<std::pair<Vec3, GameObject*>> renderList;
public:

	static	DamageIndicator& GetInstance() {
		static DamageIndicator indiCator;
		return indiCator;
	}

	void Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext) {

		//Need To Change
		shared_ptr<Shader> _shader = MANAGER_RESOURCES()->GetResource<Shader>(L"");
		if (_shader == nullptr) {
			_shader = make_shared<Shader>(L""); 
			MANAGER_RESOURCES()->AddResource(L"",_shader);
		}

		if (numberList.empty()) {
			device = _device;
			deviceContext = _deviceContext;
			for (int i = 0; i < 10; ++i) {
				std::wstring string = L"../../resources/font/num";
				string += std::to_wstring(i);
				string += L".png";
//				shared_ptr<GameObject> num = make_shared<GameObject>();
//				shared_ptr<Mesh> mesh = MANAGER_RESOURCES()->GetResource<Mesh>(L"Quad");
				shared_ptr<Material> mat = make_shared<Material>();
				mat->SetShader(_shader);
				shared_ptr<Texture> tex = MANAGER_RESOURCES()->GetOrAddTexture(L"num" + to_wstring(i), string);
				mat->SetDiffuseMap(tex);
				//TODO

//				num->Awake();
				numberList.push_back(mat);
			}
		}
	};

	void Frame() {
		float time = MANAGER_TIME()->GetDeltaTime();
		for (auto it = managingBoxList.begin(); it != managingBoxList.end();) {
			if ((*it)->textDuration <= 0.0f) {
				it = managingBoxList.erase(it);
				continue;
			}
			(*it)->textDuration -= time;
			if ((*it)->textDuration <= 0) {
				DamageIndiCatorBox* box = (*it);
				it = managingBoxList.erase(it);
				delete box;
				continue;
			}
			(*it)->pos.y += 50.0f * time;

			std::vector<int> dividingDamage;

			if ((*it)->damage >= 10) {
				int tempdamage = (*it)->damage;
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

				dividingDamage.push_back((*it)->damage);
			}
			if (dividingDamage.size() % 2 == 0) {

				for (int i = dividingDamage.size() - 1; i >= 0; --i) {
					//for (int i = 0; i < dividingDamage.size(); ++i) {
					Vec3 numPos;
					//TODO
					numPos.x = (*it)->pos.x + (-(numberList.front()->objScale.x) * (dividingDamage.size()) + ((numberList.front()->objScale.x * 2) * (dividingDamage.size() - i)));
					numPos.y = (*it)->pos.y;
					numPos.z = 1.0f;
					std::pair<Vector3, PlaneObj*> data;
					data = std::make_pair(numPos, numberList[dividingDamage[i]]);
					renderList.push_back(data);
				}

			}
			else {
				for (int i = dividingDamage.size() - 1; i >= 0; --i) {
					//for (int i =0  ; i < dividingDamage.size() ; ++i) {
					//TODO
					Vector3 numPos;
					numPos.x = (*it)->pos.x + ((-(numberList.front()->objScale.x) * (dividingDamage.size()) - (numberList.front()->objScale.x / 2)) + ((numberList.front()->objScale.x * 2) * (dividingDamage.size() - i)));
					numPos.y = (*it)->pos.y;
					numPos.z = 1.0f;
					std::pair<Vector3, PlaneObj*> data;
					data = std::make_pair(numPos, numberList[dividingDamage[i]]);
					renderList.push_back(data);
				}
			}
			++it;
		}

	};
	void Render(Matrix* matWorld, Matrix* matView, Matrix* matProj) {
		for (int i = 0; i < renderList.size(); ++i) {
			renderList[i].second->SetPos(renderList[i].first);
			renderList[i].second->UpdateMatrix();
			renderList[i].second->SetMatrix(matWorld, matView, matProj);
			renderList[i].second->Render();
		}
		renderList.clear();
	};
	void Add(DamageIndiCatorBox* IndicatorDesc) {
		managingBoxList.push_back(IndicatorDesc);
	};
	void Clear() {
		for (auto c : managingBoxList) {
			delete c;
		}
		managingBoxList.clear();
	}
private:
	DamageIndicator() {
	};
public:
	~DamageIndicator() {
		//for (auto c : numberList) {
		//	delete c;
		//}
	};
};

