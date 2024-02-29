#pragma once
static struct StructureList{
	vector<wstring> _dataList;
	StructureList(){
//		_dataList.push_back(L"bush");
		_dataList.push_back(L"rock1");
		_dataList.push_back(L"rock2");
		_dataList.push_back(L"rock3");
		_dataList.push_back(L"rock4");
		_dataList.push_back(L"rock5");
		_dataList.push_back(L"rock6");
		_dataList.push_back(L"rock7");
		_dataList.push_back(L"floatrock1");
		_dataList.push_back(L"floatrock2");
		_dataList.push_back(L"floatrock3");
		_dataList.push_back(L"floatrock4");
		_dataList.push_back(L"fog");
		_dataList.push_back(L"portal");
	}
	~StructureList() {

	}
};
class StructureObj : public GameObject
{
	using Super = GameObject;
	wstring _name = L"";
public:
	StructureObj(wstring name) { _name = name; };
	virtual ~StructureObj() {};
public:
	virtual void Awake() override;
};
