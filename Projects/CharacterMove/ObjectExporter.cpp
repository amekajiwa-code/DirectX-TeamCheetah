#include "pch.h"
#include "ObjectExporter.h"
bool ObjectExporter::OpenFile(wstring filename)
{
	FILE* fp = nullptr;
	std::string path;
	path.assign(filename.begin(), filename.end());
	//std::string path = wtm(loadPath);
	fp = fopen(path.c_str(), "r");
	if (fp == nullptr) {
		MessageBoxA(NULL, "FILE DOESN'T FOUNDED!!!!!!!!", "ERROR", MB_OK);
		return false;
	}
	int objcount = 0;
	fread(&objcount, sizeof(int), 1, fp);
	for (int i = 0; i < objcount; ++i) {
		int stringsize = 0;
		fread(&stringsize, sizeof(int), 1, fp);
		wchar_t* path;
		path = new wchar_t[stringsize];
		fread(path, sizeof(wchar_t), stringsize, fp);
		std::wstring realpath;
		realpath.append(path);
		delete[](path);
		
		std::size_t found = realpath.find_last_of(L"/");
		std::wstring divpath = realpath.substr(0, found + 1);
		if (path == L"") {
			found = realpath.find_last_of(L"\\");
			divpath = realpath.substr(0, found + 1);
		}
		found = divpath.find_last_of(L".");
		std::wstring key = realpath.substr(0,found);
		
		bool findObj;
		//TODO
		StructureList list;
		for (auto c : list._dataList) {
			if (key == c) {
				findObj = true;
				break;
			}
		}
		
		int type = 0;
		fread(&type, sizeof(int), 1, fp);
		int vectorsize = 0;
		fread(&vectorsize, sizeof(int), 1, fp);
		for (int j = 0; j < vectorsize; ++j) {
			std::vector<float> floatVec;
			floatVec.resize(9);
			fread(&floatVec.at(0), sizeof(float), 9, fp);

			int ids = 0;
			Vec3 vecPos(floatVec[0], floatVec[1], floatVec[2]);
			Vec3 vecScale(floatVec[3], floatVec[4], floatVec[5]);
			Vec3 vecRotate(floatVec[6], floatVec[7], floatVec[8]);
			if (findObj) {
				shared_ptr<StructureObj> obj= make_shared<StructureObj>(key);
				auto transformData = obj->GetOrAddTransform();
				transformData->SetLocalPosition(vecPos);
				transformData->SetLocalScale(vecScale);
				Vec3 prevRotate = transformData->GetLocalRotation();
				vecRotate = vecRotate + prevRotate;
				transformData->SetLocalRotation(vecRotate);
				_structureList.push_back(obj);
				
			}
		}

	}

	fclose(fp);
	_fcloseall();

	/*FILE* fp=nullptr;
	string path;
	path.assign(filename.begin(), filename.end());
	fp = fopen(path.c_str(), "r");
	if (fp == nullptr) {
		MessageBoxA(NULL, "FILE DOESN'T FOUNDED!!!!!!!!", "ERROR", MB_OK);
		return false;
	}
	int objcount = 0;
	fread(&objcount, sizeof(int), 1, fp);
	for (int i = 0; i < objcount; ++i) {
		int stringsize = 0;
		fread(&stringsize, sizeof(int), 1, fp);
		wchar_t* path;
		path = new wchar_t[stringsize];
		fread(path, sizeof(wchar_t), stringsize, fp);
		std::wstring realpath;
		realpath.append(path);
		delete[](path);
		int type = 0;
		fread(&type, sizeof(int), 1, fp);
		int vectorsize = 0;
		fread(&vectorsize, sizeof(int), 1, fp);
		if (vectorsize == 0)continue;

		std::size_t found = realpath.find_last_of(L"\\");
		std::wstring key = realpath.substr(found + 1);
		found = key.find_first_of(L".");
		key = key.substr(0, found);

		vector<float> allvector;
		allvector.reserve(9 * vectorsize);
		for (int j = 0; j < vectorsize; ++j) {
			std::vector<float> floatVec;
			floatVec.resize(9);
			fread(&floatVec.at(0), sizeof(float), 9, fp);

			Vec3 vecPos(floatVec[0], floatVec[1], floatVec[2]);
			Vec3 vecScale(floatVec[3], floatVec[4], floatVec[5]);
			Vec3 vecRotate(floatVec[6], floatVec[7], floatVec[8]);
			if (type == (int)ObjectType::Unit) {
				for (int k = 0; k < 9; ++k) {
					allvector.push_back(floatVec[k]);
				}
			}
		}
		if (type == (int)ObjectType::Unit) {
			enemyListforServer.insert(make_pair(key, allvector));
		}

	}




	fclose(fp);*/
	return true;
}

void ObjectExporter::LoadStructure()
{
}

void ObjectExporter::LoadEnemies()
{
}
