#include "pch.h"
#include "PlainHeightAdder.h"

shared_ptr<Plain> PlainHeightAdder::Set(HeightPlainInfo plainInfo)
{
	heightInfo = plainInfo;
	if (heightInfo.heightFilename.empty() || heightInfo.heightFilePath.empty()) {
		heightList.resize(heightInfo.col * heightInfo.row);
		for (int i = 0; i < heightList.size(); ++i) {
			heightList[i] = 0;
		}
	}
	else {

		auto imageobj = std::make_unique<DirectX::ScratchImage>();
		DirectX::TexMetadata metaData;
		ID3D11Resource* resourceTexuture;
		ID3D11Texture2D* rstexture = nullptr;
		auto makeSRV = [&]() {
			return DirectX::CreateTextureEx(DEVICE().Get(), imageobj->GetImages(), imageobj->GetImageCount(), metaData,
				D3D11_USAGE_STAGING, 0, D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ, 0, DirectX::CREATETEX_DEFAULT
				, &resourceTexuture);
			};
		auto CheckFail = [](HRESULT rs) {
			if (FAILED(rs)) {
				MessageBoxA(NULL, "UNKNOWN ERROR IN HeightMap", "ERROR", MB_OK);
				return false;
			}
			};

		HRESULT rs = DirectX::GetMetadataFromDDSFile(heightInfo.heightFilePath.c_str(), DirectX::DDS_FLAGS_NONE, metaData);
		if (SUCCEEDED(rs)) {
			rs = DirectX::LoadFromDDSFile(heightInfo.heightFilePath.c_str(), DirectX::DDS_FLAGS_NONE, &metaData, *imageobj);
			if (SUCCEEDED(rs)) {
				rs = makeSRV();
				CheckFail(rs);
			}
		}
		else if (SUCCEEDED(DirectX::GetMetadataFromWICFile(heightInfo.heightFilePath.c_str(), DirectX::WIC_FLAGS_NONE, metaData))) {
			rs = DirectX::LoadFromWICFile(heightInfo.heightFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metaData, *imageobj);
			if (SUCCEEDED(rs)) {
				rs = makeSRV();
				CheckFail(rs);
			}
		}

		//shared_ptr<Texture> heightTexture=MANAGER_RESOURCES()->LoadResource<Texture>(plainInfo.heightFilename, plainInfo.heightFilePath.c_str());

		//auto heightTexture = MANAGER_RESOURCES()->GetResource<Texture>(plainInfo.heightFilename);
		//auto heightSRV = heightTexture->GetTexture();

		D3D11_TEXTURE2D_DESC heightDesc;
		//heightSRV->GetResource(&resourceTexuture);
		//ID3D11Texture2D* texture;

		if (FAILED(resourceTexuture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&rstexture))) {
			assert(true);
		}
		rstexture->GetDesc(&heightDesc);

		D3D11_MAPPED_SUBRESOURCE mapDest;
		if (SUCCEEDED(DC()->Map((ID3D11Resource*)rstexture, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mapDest))) {
			UCHAR* pTexels = (UCHAR*)mapDest.pData;
			heightList.resize(heightDesc.Width * heightDesc.Height);
			for (UINT row = 0; row < heightDesc.Height; row++)
			{
				UINT rowStart = row * mapDest.RowPitch;
				for (UINT col = 0; col < heightDesc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					//const_cast<std::Vec<VertexTextureNormalTangentData>&>(geoVertices)[row * heightDesc.Width + col].position.y = (float)uRed;	/// DWORD이므로 pitch/4	
					heightList[row * heightDesc.Width + col] =uRed;	/// DWORD이므로 pitch/4	
				}
			}
			DC()->Unmap(rstexture, D3D11CalcSubresource(0, 0, 1));
			heightInfo.col = heightDesc.Width;
			heightInfo.row = heightDesc.Height;
		}
	}
	plain = make_shared<Plain>();
	plain->Set(dynamic_cast<Plaininfo&>(heightInfo));

	auto refmesh = MANAGER_RESOURCES()->GetResource<Mesh>(plain->GetPlainDesc().meshKey);
	auto _geo = refmesh->GetGeo();
	auto& geoVertices = _geo->GetVertices();
	for (int i = 0; i < geoVertices.size(); ++i) {
		const_cast<PlainVector&>(geoVertices)[i].position.y = (float)heightList[i];
	}
	auto refIndexList = _geo->GetIndices();
	for (int j = 0; j < refIndexList.size(); j += 3) {
		Vec3 p1 = geoVertices[refIndexList[j + 0]].position;
		Vec3 p2 = geoVertices[refIndexList[j + 1]].position;
		Vec3 p0 = geoVertices[refIndexList[j + 2]].position;

		Vec3 e1 = p1 - p0;
		Vec3 e2 = p2 - p0;
		Vec3 normal =e1.Cross(e2);
		normal.Normalize();
		const_cast<PlainVector&>(geoVertices)[refIndexList[j + 0]].normal += normal;
		const_cast<PlainVector&>(geoVertices)[refIndexList[j + 1]].normal += normal;
		const_cast<PlainVector&>(geoVertices)[refIndexList[j + 2]].normal += normal;
	}
	for (int i = 0; i < geoVertices.size(); ++i) {
		const_cast<PlainVector&>(geoVertices)[i].normal.Normalize();
	}
	D3D11_MAPPED_SUBRESOURCE resource;
	DC()->Map(refmesh->GetVertexBuffer()->GetBuffer().Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &resource);
	memcpy(resource.pData,&geoVertices.at(0), sizeof(VertexTextureNormalTangentData) * geoVertices.size());
	DC()->Unmap(refmesh->GetVertexBuffer()->GetBuffer().Get(), 0);

	return plain;

}
