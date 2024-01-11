#include "pch.h"
#include "Converter.h"
#include <filesystem>
#include "engine/Utils.h"
#include "engine/FileUtils.h"

Converter::Converter()
{
	_importer = make_shared<Assimp::Importer>();
}

Converter::~Converter()
{
}

void Converter::ReadModelData(aiNode* node, int32 index, int32 parent)
{
	if (node == nullptr) return;

	shared_ptr<asBone> bone = make_shared<asBone>();
	bone->index = index;
	bone->parent = parent;
	bone->name = node->mName.C_Str();
	//Relative Transform
	Matrix transform(node->mTransformation[0]);
	bone->transform = transform.Transpose();

	Matrix matParnet = Matrix::Identity;
	if (parent >= 0)
	{
		matParnet = _bones[parent]->transform;
	}
	//Root기준 Final Local Transform을 얻는다
	bone->transform = bone->transform * matParnet;
	_bones.push_back(bone);

	//Mesh
	ReadMeshData(node, index);

	//재귀
	for (uint32 i = 0; i < node->mNumChildren; i++)
	{
		ReadModelData(node->mChildren[i], _bones.size(), index);
	}
}

void Converter::ReadMeshData(aiNode* node, int32 bone)
{

	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		shared_ptr<asMesh> mesh = make_shared<asMesh>();
		mesh->name = node->mName.C_Str();
		mesh->boneIndex = bone;

		uint32 index = node->mMeshes[i];
		const aiMesh* srcMesh = _scene->mMeshes[index];

		// Material Name
		const aiMaterial* material = _scene->mMaterials[srcMesh->mMaterialIndex];
		mesh->materialName = material->GetName().C_Str();

		const uint32 startVertex = mesh->vertices.size();

		for (uint32 v = 0; v < srcMesh->mNumVertices; v++)
		{
			// Vertex
			VertexType vertex;
			::memcpy(&vertex.position, &srcMesh->mVertices[v], sizeof(Vec3));

			// UV
			if (srcMesh->HasTextureCoords(0))
				::memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Vec2));

			// Normal
			if (srcMesh->HasNormals())
				::memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Vec3));

			// Tangent
			if (srcMesh->HasTangentsAndBitangents())
				::memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Vec3));

			mesh->vertices.push_back(vertex);
		}

		// Index
		for (uint32 f = 0; f < srcMesh->mNumFaces; f++)
		{
			aiFace& face = srcMesh->mFaces[f];

			for (uint32 k = 0; k < face.mNumIndices; k++)
				mesh->indices.push_back(face.mIndices[k] + startVertex);
		}
		_meshes.push_back(mesh);
	}
}

void Converter::WriteModelFile(wstring finalPath)
{
	//디렉토리 생성
	auto path = filesystem::path(finalPath);
	filesystem::create_directory(path.parent_path());
	//파일을 쓰기모드로 생성
	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(finalPath, FileMode::Write);
	//Bone Data Input
	file->Write<uint32>(_bones.size());
	for (auto& bone : _bones)
	{
		file->Write<int32>(bone->index);
		file->Write<string>(bone->name);
		file->Write<int32>(bone->parent);
		file->Write<Matrix>(bone->transform);
	}
	//Mesh Data Input
	file->Write<uint32>(_meshes.size());
	for (auto& meshData : _meshes)
	{
		file->Write<string>(meshData->name);
		file->Write<int32>(meshData->boneIndex);
		file->Write<string>(meshData->materialName);
		//Vertex
		file->Write<uint32>(meshData->vertices.size());
		file->Write(&meshData->vertices[0], sizeof(VertexType) * meshData->vertices.size());
		//Index
		file->Write<uint32>(meshData->indices.size());
		file->Write(&meshData->indices[0], sizeof(uint32) * meshData->indices.size());
	}
}

void Converter::WriteSkinFile(wstring finalPath)
{
	auto path = filesystem::path(finalPath);
	filesystem::create_directory(path.parent_path());

	//Write CSV File
	{
		FILE* file;
		::fopen_s(&file, Utils::ToString(finalPath).c_str(), "w");

		for (shared_ptr<asBone>& bone : _bones)
		{
			string name = bone->name;
			::fprintf(file, "%d,%s\n", bone->index, bone->name.c_str());
		}

		::fprintf(file, "\n");

		for (shared_ptr<asMesh>& mesh : _meshes)
		{
			string name = mesh->name;
			::fprintf(file, "%s,", name.c_str());
			::fprintf(file, "\n");

			for (UINT i = 0; i < mesh->vertices.size(); i++)
			{
				Vec3 p = mesh->vertices[i].position;
				Vec4 indices = mesh->vertices[i].blendIndices;
				Vec4 weights = mesh->vertices[i].blendWeights;

				::fprintf(file, "%f,%f,%f,", p.x, p.y, p.z);
				::fprintf(file, "%f,%f,%f,%f,", indices.x, indices.y, indices.z, indices.w);
				::fprintf(file, "%f,%f,%f,%f\n", weights.x, weights.y, weights.z, weights.w);
			}
		}

		::fclose(file);
	}
}

uint32 Converter::GetBoneIndex(const string& name)
{
	for (auto& bone : _bones)
	{
		if (bone->name == name)
			return bone->index;
	}

	assert(false);
	return 0;
}

void Converter::ReadSkinData()
{
	for (uint32 i = 0; i < _scene->mNumMeshes; i++)
	{
		aiMesh* srcMesh = _scene->mMeshes[i];
		if (srcMesh->HasBones() == false)
			continue;

		shared_ptr<asMesh> mesh = _meshes[i];

		vector<asBoneWeights> tempVertexBoneWeights;
		tempVertexBoneWeights.resize(mesh->vertices.size());

		// Bone을 순회하면서 연관된 VertexId, Weight를 구해서 기록한다.
		for (uint32 b = 0; b < srcMesh->mNumBones; b++)
		{
			aiBone* srcMeshBone = srcMesh->mBones[b];
			uint32 boneIndex = GetBoneIndex(srcMeshBone->mName.C_Str());

			for (uint32 w = 0; w < srcMeshBone->mNumWeights; w++)
			{
				uint32 index = srcMeshBone->mWeights[w].mVertexId;
				float weight = srcMeshBone->mWeights[w].mWeight;
				tempVertexBoneWeights[index].AddWeights(boneIndex, weight);
			}
		}

		// 최종 결과 계산
		for (uint32 v = 0; v < tempVertexBoneWeights.size(); v++)
		{
			tempVertexBoneWeights[v].Normalize();

			asBlendWeight blendWeight = tempVertexBoneWeights[v].GetBlendWeights();
			mesh->vertices[v].blendIndices = blendWeight.indices;
			mesh->vertices[v].blendWeights = blendWeight.weights;
		}
	}
}

shared_ptr<asAnimation> Converter::ReadAnimationData(aiAnimation* srcAnimation)
{
	shared_ptr<asAnimation> animation = make_shared<asAnimation>();
	animation->name = srcAnimation->mName.C_Str();
	animation->duration = (float)srcAnimation->mDuration;
	animation->frameCount = srcAnimation->mDuration+1;
	animation->frameRate = srcAnimation->mTicksPerSecond;

	//animation->frameRate = (float)srcAnimation->mTicksPerSecond;
	//uint32 num = (srcAnimation->mChannels[0]->mNumPositionKeys + srcAnimation->mChannels[0]->mNumRotationKeys + srcAnimation->mChannels[0]->mNumScalingKeys) / 3;
	//animation->frameCount = num;

	map<string, shared_ptr<asAnimationNode>> cacheAnimNodes;
	for (uint32 i = 0; i < srcAnimation->mNumChannels; i++)
	{
		aiNodeAnim* srcNode = srcAnimation->mChannels[i];
		_animNodeList.push_back(srcNode);

		// 애니메이션 노드 데이터 파싱
		shared_ptr<asAnimationNode> node = ParseAnimationNode(animation, srcNode);

		// 현재 찾은 노드 중에 제일 긴 시간으로 애니메이션 시간 갱신
		//animation->duration = max(animation->duration, node->keyframe.back().time);

		cacheAnimNodes[srcNode->mNodeName.C_Str()] = node;
	}

	ReadKeyframeData(animation, _scene->mRootNode, cacheAnimNodes);

	return animation;
}

void Converter::ReadKeyframeData(shared_ptr<asAnimation> animation, aiNode* srcNode, map<string, shared_ptr<asAnimationNode>>& cache)
{
	shared_ptr<asKeyframe> keyframe = make_shared<asKeyframe>();
	keyframe->boneName = srcNode->mName.C_Str();

	shared_ptr<asAnimationNode> findNode = cache[srcNode->mName.C_Str()];

	for (uint32 i = 0; i < animation->frameCount; i++)
	{
		asKeyframeData frameData;

		if (findNode == nullptr)
		{
			Matrix transform(srcNode->mTransformation[0]);
			transform = transform.Transpose();
			frameData.time = (float)i;
			transform.Decompose(OUT frameData.scale, OUT frameData.rotation, OUT frameData.translation);
		}
		else
		{
			frameData = findNode->keyframe[i];
		}

		keyframe->transforms.push_back(frameData);
	}

	// 애니메이션 키프레임 채우기
	animation->keyframes.push_back(keyframe);

	for (uint32 i = 0; i < srcNode->mNumChildren; i++)
		ReadKeyframeData(animation, srcNode->mChildren[i], cache);
}

void Converter::WriteAnimationData(shared_ptr<asAnimation> animation, wstring finalPath)
{
	auto path = filesystem::path(finalPath);

	// 폴더가 없으면 만든다.
	filesystem::create_directory(path.parent_path());

	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(finalPath, FileMode::Write);

	file->Write<string>(animation->name);
	file->Write<float>(animation->duration);
	file->Write<float>(animation->frameRate);
	file->Write<uint32>(animation->frameCount);
	file->Write<uint32>(animation->keyframes.size());

	for (shared_ptr<asKeyframe> keyframe : animation->keyframes)
	{
		file->Write<string>(keyframe->boneName);

		file->Write<uint32>(keyframe->transforms.size());
		file->Write(&keyframe->transforms[0], sizeof(asKeyframeData) * keyframe->transforms.size());
	}
}

shared_ptr<asAnimationNode> Converter::ParseAnimationNode(shared_ptr<asAnimation> animation, aiNodeAnim* srcNode)
{
	std::shared_ptr<asAnimationNode> node = make_shared<asAnimationNode>();
	node->name = srcNode->mNodeName;

	uint32 keyCount = max(max(srcNode->mNumPositionKeys, srcNode->mNumScalingKeys), srcNode->mNumRotationKeys);

	for (uint32 k = 0; k < keyCount; k++)
	{
		asKeyframeData frameData;
		// Position
		{
			aiVectorKey key = srcNode->mPositionKeys[k];
			frameData.time = (float)key.mTime;
			::memcpy_s(&frameData.translation, sizeof(Vec3), &key.mValue, sizeof(aiVector3D));
		}

		// Rotation
		{
			aiQuatKey key = srcNode->mRotationKeys[k];
			frameData.time = (float)key.mTime;

			frameData.rotation.x = key.mValue.x;
			frameData.rotation.y = key.mValue.y;
			frameData.rotation.z = key.mValue.z;
			frameData.rotation.w = key.mValue.w;
		}

		// Scale
		{
			aiVectorKey key = srcNode->mScalingKeys[k];
			frameData.time = (float)key.mTime;
			::memcpy_s(&frameData.scale, sizeof(Vec3), &key.mValue, sizeof(aiVector3D));
		}

		node->keyframe.push_back(frameData);
	}

	// Keyframe 늘려주기
	if (node->keyframe.size() < animation->frameCount)
	{
		uint32 count = animation->frameCount - node->keyframe.size();
		asKeyframeData keyFrame = node->keyframe.back();

		for (uint32 n = 0; n < count; n++)
			node->keyframe.push_back(keyFrame);
	}

	return node;
}

void Converter::ExportModelData(wstring savePath)
{
	wstring finalPath = savePath;
	size_t findSize = finalPath.find_last_of(L".");
	wstring finalSkinDataPath = finalPath.substr(0, findSize) + L".csv";

	ReadModelData(_scene->mRootNode, -1, -1);
	ReadSkinData();
	WriteSkinFile(finalSkinDataPath);
	WriteModelFile(finalPath);
}

bool Converter::ReadMaterialData()
{
	if (_scene->mNumMaterials <= 0)
	{
		return false;
	}

	for (uint32 i = 0; i < _scene->mNumMaterials; i++)
	{
		//source
		aiMaterial* srcMaterial = _scene->mMaterials[i];
		//Custom Pasing
		shared_ptr<asMaterial> material = make_shared<asMaterial>();
		material->name = srcMaterial->GetName().C_Str();

		//Light 영향도
		aiColor3D color;
		//Ambient
		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->ambient = Color(color.r, color.g, color.b, 1.0f);
		//Diffuse
		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->diffuse = Color(color.r, color.g, color.b, 1.0f);
		//Specular
		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->specular = Color(color.r, color.g, color.b, 1.0f);
		srcMaterial->Get(AI_MATKEY_SHININESS, material->specular.w);
		//Emissive
		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->emissive = Color(color.r, color.g, color.b, 1.0f);

		//텍스쳐
		aiString file;
		//Diffuse Texture
		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->diffuseFile = file.C_Str();
		//Specular Texture
		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->specularFile = file.C_Str();
		//Normal Texture
		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->normalFile = file.C_Str();

		//Push Data
		_materials.push_back(material);
	}

	return true;
}

void Converter::WriteMaterialData(wstring finalPath)
{
	//디렉토리 생성
	auto path = filesystem::path(finalPath);
	filesystem::create_directory(path.parent_path());
	string folder = path.parent_path().string();
	//XML WRITE
	//doc 생성
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	//버전 정의
	tinyxml2::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);
	//머티리얼 목록
	tinyxml2::XMLElement* root = document->NewElement("Materials");
	document->LinkEndChild(root);
	
	for (auto material : _materials)
	{
		//머티리얼 당
		tinyxml2::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);
		tinyxml2::XMLElement* element = nullptr;
		//Name
		element = document->NewElement("Name");
		element->SetText(material->name.c_str());
		node->LinkEndChild(element);
		//Diffuse Texture
		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, material->diffuseFile).c_str());
		node->LinkEndChild(element);
		//Specular Texture
		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, material->specularFile).c_str());
		node->LinkEndChild(element);
		//NormalMap Texture
		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, material->normalFile).c_str());
		node->LinkEndChild(element);
		//Ambient Influence
		element = document->NewElement("Ambient");
		element->SetAttribute("R", material->ambient.x);
		element->SetAttribute("G", material->ambient.y);
		element->SetAttribute("B", material->ambient.z);
		element->SetAttribute("A", material->ambient.w);
		node->LinkEndChild(element);
		//Diffuse Influence
		element = document->NewElement("Diffuse");
		element->SetAttribute("R", material->diffuse.x);
		element->SetAttribute("G", material->diffuse.y);
		element->SetAttribute("B", material->diffuse.z);
		element->SetAttribute("A", material->diffuse.w);
		node->LinkEndChild(element);
		//Specular Influence
		element = document->NewElement("Specular");
		element->SetAttribute("R", material->specular.x);
		element->SetAttribute("G", material->specular.y);
		element->SetAttribute("B", material->specular.z);
		element->SetAttribute("A", material->specular.w);
		node->LinkEndChild(element);
		//Emissive Influence
		element = document->NewElement("Emissive");
		element->SetAttribute("R", material->emissive.x);
		element->SetAttribute("G", material->emissive.y);
		element->SetAttribute("B", material->emissive.z);
		element->SetAttribute("A", material->emissive.w);
		node->LinkEndChild(element);
	}

	//File Save
	document->SaveFile(Utils::ToString(finalPath).c_str());
}

string Converter::WriteTexture(string saveFolder, string file)
{
	string fileName = filesystem::path(file).filename().string();
	string folderName = filesystem::path(saveFolder).filename().string();

	const aiTexture* srcTexture = _scene->GetEmbeddedTexture(file.c_str());
	if (srcTexture)
	{
		string pathStr = (filesystem::path(saveFolder) / fileName).string();

		if (srcTexture->mHeight == 0)
		{
			shared_ptr<FileUtils> file = make_shared<FileUtils>();
			file->Open(Utils::ToWString(pathStr), FileMode::Write);
			file->Write(srcTexture->pcData, srcTexture->mWidth);
		}
		else
		{
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
			desc.Width = srcTexture->mWidth;
			desc.Height = srcTexture->mHeight;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_IMMUTABLE;

			D3D11_SUBRESOURCE_DATA subResource = { 0 };
			subResource.pSysMem = srcTexture->pcData;

			ComPtr<ID3D11Texture2D> texture;
			HRESULT hr = DEVICE()->CreateTexture2D(&desc, &subResource, texture.GetAddressOf());
			CHECK(hr);

			DirectX::ScratchImage img;
			::CaptureTexture(DEVICE().Get(), DC().Get(), texture.Get(), img);

			// Save To File
			hr = DirectX::SaveToDDSFile(*img.GetImages(), DirectX::DDS_FLAGS_NONE, Utils::ToWString(fileName).c_str());
			CHECK(hr);
		}
	}
	else
	{
		string originStr = (filesystem::path(_assetPath) / folderName / file).string();
		Utils::Replace(originStr, "\\", "/");

		string pathStr = (filesystem::path(saveFolder) / fileName).string();
		Utils::Replace(pathStr, "\\", "/");

		::CopyFileA(originStr.c_str(), pathStr.c_str(), false);
	}

	return fileName;
}

void Converter::ExportMaterialData(wstring savePath)
{
	wstring finalPath = savePath;
	ReadMaterialData();
	WriteMaterialData(finalPath);
}

void Converter::ExportAnimationData(wstring savePath, uint32 index)
{
	wstring finalPath = savePath;
	assert(index < _scene->mNumAnimations);

	_animation = ReadAnimationData(_scene->mAnimations[index]);
	WriteAnimationData(_animation, finalPath);
}

void Converter::Init()
{
	if (_scene != nullptr)
	{
		if (_meshes.size() > 0)
		{
			for (auto mesh : _meshes)
			{
				mesh = nullptr;
			}
			_meshes.clear();
		}
		if (_bones.size() > 0)
		{
			for (auto bone : _bones)
			{
				bone = nullptr;
			}
			_bones.clear();
		}
		if (_materials.size() > 0)
		{
			for (auto material : _materials)
			{
				material = nullptr;
			}
			_materials.clear();
		}

		_importer->FreeScene();
		_scene = nullptr;
	}
}

void Converter::ExportAnimationData(wstring& name, wstring& savePath, uint32 index)
{
	wstring finalPath = savePath;
	assert(index < _scene->mNumAnimations);

	_animation = ReadAnimationData(_scene->mAnimations[index]);
	_animation->name = Utils::ToString(name);
	WriteAnimationData(_animation, finalPath);
}

void Converter::ReadAssetFile(ModelType type, wstring fileName)
{
	//Type Check
	switch (type)
	{
	case ModelType::Skeletal:
		//_currentType = ModelType::Skeletal;
		_assetPath = RESOURCES_ADDR_ASSET_SKELETAL;
		_modelPath = RESOURCES_ADDR_MESH_SKELETAL;
		_texturePath = RESOURCES_ADDR_TEXTURE_SKELETAL;
		break;
	case ModelType::Static:
		//_currentType = ModelType::Static;
		_assetPath = RESOURCES_ADDR_ASSET_STATIC;
		_modelPath = RESOURCES_ADDR_MESH_STATIC;
		_texturePath = RESOURCES_ADDR_TEXTURE_STATIC;
		break;
	}
	//Create FilePath
	wstring fileStr = _assetPath + fileName;
	//File path Check
	auto p = std::filesystem::path(fileStr);
	//is Exists
	if (std::filesystem::exists(p))
	{
		//File Read
		_scene = _importer->ReadFile(
			Utils::ToString(fileStr),
			aiProcess_MakeLeftHanded |
			aiProcess_FlipUVs |
			aiProcess_FlipWindingOrder |
			aiProcess_ImproveCacheLocality |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_Triangulate |
			aiProcess_GenUVCoords |
			aiProcess_TransformUVCoords |
			aiProcess_GenNormals |
			aiProcess_CalcTangentSpace
		);
		//is not Read
		assert(_scene != nullptr);
	}
}

bool Converter::ReadAssetFile(wstring filePath)
{
	//File path Check
	auto p = std::filesystem::path(filePath);
	//is Exists
	if (std::filesystem::exists(p))
	{
		//File Read
		_scene = _importer->ReadFile(
			Utils::ToString(filePath),
			aiProcess_MakeLeftHanded |
			aiProcess_FlipUVs |
			aiProcess_FlipWindingOrder |
			aiProcess_ImproveCacheLocality |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_Triangulate |
			aiProcess_GenUVCoords |
			aiProcess_TransformUVCoords |
			aiProcess_GenNormals |
			aiProcess_CalcTangentSpace 
		);
		//is not Read
		if (_scene == nullptr)
			return false;
	}
	return true;
}

