#pragma once
#include "level.h"
#include "stringArray.h"
#include "dxManager.h"
#include "dxCamera.h"

class levelManager
{
private:
	level * m_level;
	stringArray * fileNames;
	dxManager * dxMgr;
	dxCamera * camera;
	int numLevels;

public:
	levelManager(void);
	~levelManager(void);
	void init(std::string filename, dxManager * a_dxMgr, dxCamera * a_camera);
	bool setLevel(int);
	level * getLevel();
};
