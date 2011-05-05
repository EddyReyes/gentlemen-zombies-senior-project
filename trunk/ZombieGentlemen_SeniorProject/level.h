#pragma once
#include "dxManager.h"
#include "objectManager.h"
#include "inputData.h"
#include "directInput.h"
#include "physics.h"
#include "stringArray.h"
#include "background.h"
#include "HUD.h"

class level
{
private:
	objectManager * objMgr;
	stringArray * files;
	cubeMap * m_map;
	background * backGrnd;
	HUD * p1HUD;


public:
	level();
	void initLevel(dxManager* a_dxMgr, std::string filename);
	void setMusic(char*);//sets the music for the level
	void draw();
	void handleInput(inputData * input, int now);
	void update(float);
	~level();//deconstructor

	//debug code
	void pop();
	void moveObject(D3DXVECTOR3);//may or maynot stay that way
	object* getobject(){return objMgr->getObject();}
	objectManager* getManager(){return objMgr;}
};