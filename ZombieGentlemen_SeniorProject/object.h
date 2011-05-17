#pragma once
#include "XYPlane.h"
#include "dxCube.h"
#include "dxManager.h"
#include "collisionRect.h"
#include "physics.h"
#include "intVector.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

#define collidingLeft collData & 1
#define collidingRight (collData & (1<<1)) >> 1
#define collidingTop (collData & (1<<2)) >> 2
#define collidingBottom (collData & (1<<3)) >> 3


class object
{
protected:
	XYPlane * plane;
	dxCube * cube;
	collisionRect * collRect;
	collisionRect * targetCollRect;
	object * target;
	bool collisionToggle;
	D3DXVECTOR3 oldPos;
	bool colliding;
	int collData, oldCollData, objectIndex;
	intVector * collHistory;
	physics * phys;

public:

	// constructors
	object();
	object(dxManager* a_dxMgr, std::string imgFile);
	object(XYPlane * a_plane);
	object(dxCube * a_cube);
	// destructor
	~object();

	// load functions
	void loadParametersFromTxtFile(std::string filename);
	void loadParameters(float x, float y, float z, float width, float height, float depth,
		 int imageRows, int imageColumns, float leftOffset, float topOffset, float rightOffset,
		 float bottomOffset);

	// member functions
	void draw();
	void checkCollision();
	void updatePhysics();
	void clear();
	void recordPosition();
	void handleCollision();

	// mutators
	void toggleCollision();
	void collisionToggleOn();
	void collisionToggleOff();
	void togglePhysics();
	void toggleImage();		
	void setPosition(float a_x, float a_y, float a_z);	
	void setPosition(D3DXVECTOR3);	
	void setTargetCollision(collisionRect * a_collRect);
	void setTarget(object * a_target);
	bool setSprite(int row, int column);
	void setObjectIndex(int a_index);
	
	// accesors	
	D3DXVECTOR3 * getPosition();
	collisionRect * getCollisionRect();
	physics * getPhysics();
	XYPlane * getXYPlane();
	dxCube * getDxCube();
	bool isColliding();
	bool isCollidable();
	int getCollData();
	int getObjectIndex();
	intVector * getCollHistory();
};