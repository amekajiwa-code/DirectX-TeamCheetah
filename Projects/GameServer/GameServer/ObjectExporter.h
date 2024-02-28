#pragma once

class ObjectExporter
{
	bool isLoaded = false;
public:
	vector<pair<wstring, Vec3>> enemyListforServer;
public:
	bool OpenFile(wstring filename);
};

