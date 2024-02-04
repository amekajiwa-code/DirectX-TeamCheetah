#pragma once
#include "pch.h"
#include "Plain.h"
struct HeightPlainInfo :public Plaininfo{
	std::wstring heightFilePath;
	std::wstring heightFilename;
};

class PlainHeightAdder: public MonoBehaviour
{
	shared_ptr<Plain> plain;
	HeightPlainInfo heightInfo;
	std::vector<UCHAR> heightList;
public:
	shared_ptr<Plain> Set(HeightPlainInfo plainInfo);
	HeightPlainInfo GetHeightInfo() {
		return heightInfo;
	};
	const vector<UCHAR>& GetHeightList() {
		return heightList;
	};
	float GetHeightFromList(int posX, int posZ) {
		return heightList[(abs(posX - (int)heightInfo.row)-1) * heightInfo.row + posZ];
//		return heightList[posX * heightInfo.row + abs(posZ - (int)heightInfo.col)];
	}
	shared_ptr<Plain> GetPlain() {
		return plain;
	}
};

