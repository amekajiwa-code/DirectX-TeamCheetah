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
		printf("FILE DOESN'T FOUNDED!!!!!!!!");
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
		if (found > 1000) {
			found = realpath.find_last_of(L"\\");
		}
		wstring divpath = realpath.substr(found + 1, realpath.size());
		found = divpath.find_last_of(L".");
		std::wstring key = divpath.substr(0, found);

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
			vecPos.z = vecPos.z * -1.0f;

			enemyListforServer.push_back(make_pair(key,vecPos));

		}

	}

	fclose(fp);
	_fcloseall();
	return true;
}