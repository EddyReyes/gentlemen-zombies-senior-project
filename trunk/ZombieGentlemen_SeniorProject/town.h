#pragma once
#include "XYPlane.h"
#include "objectManager.h"
#include "dxCamera.h"

// this class will contain the towns map, objects, and characters

class town
{
private:
	XYPlane * map;
	objectManager * objMgr;
	dxCamera * camera;

public:
	town();
	~town();
	void init();
	void update();
	void draw();
};