#pragma once
#include "dxManager.h"
#include "XYPlane.h"
#include "objectManager.h"
#include "dxCamera.h"

// this class will contain the towns map, objects, and characters

class town
{
private:
	XYPlane* map;
	dxCamera * camera;

public:
	town();
	town(dxManager*);
	~town();
	void init();
	void update();
	void draw();
};