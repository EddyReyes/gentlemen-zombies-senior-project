#pragma once
#include "dxManager.h"
#include "objectManager.h"
#include "physics.h"
#include "stringArray.h"
class level
{
private:
	objectManager* ObjMan;
	stringArray* files;
	cubeMap* m_map;
public:
	level();
	level(dxManager*, char*);//initializes objectmanager
	void setMusic(char*);//sets the music for the level
	void draw();
	void update(float);
	~level();//deconstructor

	//debug code
	void pop();
	void moveObject(D3DXVECTOR3);//may or maynot stay that way
	object* getobject(){return ObjMan->getObject();}
	physics* getObjectPhysic(){return ObjMan->getObject()->getPhysics();}
	objectManager* getManager(){return ObjMan;}
};