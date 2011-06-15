#pragma once
#include "dxManager.h"
#include "XYPlane.h"
#include "objectManager.h"
#include "dxCamera.h"
#include "directInput.h"
#include "inputData.h"
#include "stringArray.h"

#define max_positions 5

// this class will contain the towns map, objects, and characters
class town
{
private:
	XYPlane* map;
	dxCamera * camera;
	XYPlane* m_object;
	XYPlane* buildings;
public:
	town();
	~town();
	void init(dxManager * a_dxMgr, dxCamera *, char *file, char*file2);
	int update(inputData * input,int now);
	void draw();
};