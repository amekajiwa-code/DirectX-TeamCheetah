#include "pch.h"
#include "DamageIndicator.h"



	DamageIndicator& DamageIndicator::GetInstance() {
		static DamageIndicator indiCator;
		return indiCator;
	}

	void DamageIndicator::Init() {

		//Need To Change
		if (_shader == nullptr) {
			_shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Damage");
			if (_shader == nullptr) {
				_shader = make_shared<Shader>(L"Damage.fx");
				MANAGER_RESOURCES()->AddResource(L"Damage", _shader);
				numArray = _shader->GetSRV("NumListMap");
			}

			CreateInstance();
			CreateMesh();

			for (int i = 0; i < 10; ++i) {
				std::wstring string = L"../../Resources/Font/num/";
				string += std::to_wstring(i);
				string += L".png";

				shared_ptr<Texture> tex = MANAGER_RESOURCES()->GetOrAddTexture(L"num" + to_wstring(i), string);
				numSRVs.push_back(tex->GetTexture().Get());
			}

		}
	};
	void DamageIndicator::Frame() {
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
			(it)->pos.y += 50.0f * time / 2;

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
					numPos.y = 1;// (it)->pos.y;
					numPos.z = 1;// (it)->pos.z;
					numPos.x = (numPos.x - (it)->pos.x) / 2;

					IndicatorInstance data;
					data.num = dividingDamage[i];
					auto look = (cam->GetTransform()->GetLookVector());
					Matrix billmat = Matrix::CreateBillboard(it->pos, cam->GetTransform()->GetPosition(), cam->GetTransform()->GetUpVector(), &look);

					Vec3 dePos;
					Vec3 deScale;
					Quaternion deRot;
					billmat.Decompose(deScale, deRot, dePos);


					Matrix detransmat = Matrix::CreateTranslation(numPos);
					Matrix rotate = Matrix::CreateFromQuaternion(deRot);
					Matrix transmat = Matrix::CreateTranslation((it)->pos);
					data.world *= detransmat;
					data.world *= rotate;
					data.world *= transmat;

					renderList.push_back(data);
				}

			}
			else {
				for (int i = dividingDamage.size() - 1; i >= 0; --i) {
					//for (int i =0  ; i < dividingDamage.size() ; ++i) {
					//TODO
					Vec3 numPos;
					numPos.x = (it)->pos.x + ((-(xScale) * (dividingDamage.size()) - (xScale / 2)) + ((xScale * 2) * (dividingDamage.size() - i)));
					numPos.y = 1;// (it)->pos.y;
					numPos.z = 1;// (it)->pos.z;
					numPos.x = (numPos.x - (it)->pos.x) / 2;

					IndicatorInstance data;
					data.num = dividingDamage[i];
					auto look = (cam->GetTransform()->GetLookVector());
					Matrix billmat = Matrix::CreateBillboard(it->pos, cam->GetTransform()->GetPosition(), cam->GetTransform()->GetUpVector(), &look);

					Vec3 dePos;
					Vec3 deScale;
					Quaternion deRot;
					billmat.Decompose(deScale, deRot, dePos);

					Matrix detransmat = Matrix::CreateTranslation(numPos);
					Matrix rotate = Matrix::CreateFromQuaternion(deRot);
					Matrix transmat = Matrix::CreateTranslation((it)->pos);
					data.world *= detransmat;
					data.world *= rotate;
					data.world *= transmat;

					renderList.push_back(data);
				}
			}
			++it;
		}

	};
	void DamageIndicator::Render() {
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

		_shader->DrawIndexedInstanced(0, 0, _mesh->GetIndexBuffer()->GetCount(), renderList.size());
		renderList.clear();
	};
	DamageIndicator::DamageIndicator() {
	};
	void DamageIndicator::CreateInstance() {

		instanceBuffer = make_shared<VertexBuffer>();
		vector<IndicatorInstance> temp(500);
		instanceBuffer->CreateVertexBuffer(temp, /*slot*/1, /*cpuWrite*/true);

	};
	void DamageIndicator::CreateMesh() {
		_mesh = make_shared<Mesh>();

		vector<VertexTextureNormalTangentData> vtx;
		vtx.resize(4);

		vtx[0].position = Vec3(-xScale / 2.f, -yScale / 2.f, 0.f);
		vtx[1].position = Vec3(-xScale / 2.f, yScale / 2.f, 0.f);
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
	};
	DamageIndicator::~DamageIndicator() {
	};