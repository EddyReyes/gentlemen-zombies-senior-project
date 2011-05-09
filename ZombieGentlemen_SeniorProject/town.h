#pragma once
#include "dxManager.h"
#include "XYPlane.h"
#include "objectManager.h"
#include "dxCamera.h"
#include "directInput.h"
#include "inputData.h"


// this class will contain the towns map, objects, and characters

class town
{
private:
	XYPlane* map;
	dxCamera * camera;
	object * m_object;
	D3DXVECTOR3* m_points;
public:
	town();
	~town();
	void init(dxManager * a_dxMgr);
	int update(inputData * input,int now);
	void draw();
};