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
	object * m_object;
public:
	town();
	~town();
	void init(dxManager * a_dxMgr);
	void update();
	void draw();
};