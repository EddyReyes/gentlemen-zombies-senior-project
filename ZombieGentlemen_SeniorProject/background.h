#pragma once

#include "planeMap.h"
#include "stringArray.h"
#include "dxManager.h"
#include "cubeMap.h"

class background
{
private:
	planeMap ** planeMaps;
	stringArray * mapNames;
	stringArray * imgNames;
	int numPlaneMaps;

public:
	background();
	~background();
	void initBackground(dxManager * dxMgr, std::string filename);
	void draw();
};