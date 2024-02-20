#include "pch.h"
#include "StructList.h"

void StructureObj::Awake()
{
	auto _obj = make_shared<GameObject>();
	wstring objName = _name;

	//Character
	{
		shared_ptr<Model> model = make_shared<Model>();
		{	
			wstring MeshAdr = RESOURCES_ADDR_MESH_STATIC;
			MeshAdr += objName;
			MeshAdr += L"/";
			MeshAdr += objName;
			MeshAdr += L".mesh";

			wstring MaterialAdr = RESOURCES_ADDR_TEXTURE_STATIC;
			MaterialAdr += objName;
			MaterialAdr += L"/";
			MaterialAdr += objName;
			MaterialAdr += L".xml";

			model->ReadModel(MeshAdr);
			model->ReadMaterial(MaterialAdr);
		}
		const auto& shader = MANAGER_RESOURCES()->GetResource<Shader>(L"Default");
		shared_ptr<ModelRenderer> tempModelRenderer = make_shared<ModelRenderer>(shader);
		{
			tempModelRenderer->SetModel(model);
			tempModelRenderer->SetPass(0);
		}
		this->AddComponent(tempModelRenderer);

		Vec3 rot = this->GetOrAddTransform()->GetLocalRotation();
		rot.x += ::XMConvertToRadians(90.f);
		rot.y -= ::XMConvertToRadians(90.f);
		this->GetTransform()->SetLocalRotation(rot);
	}
	SetName(objName);

	Super::Awake();
}
