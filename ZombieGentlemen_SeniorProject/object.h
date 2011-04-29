#pragma once
#include "XYPlane.h"
#include "dxCube.h"
#include "dxManager.h"
#include "collisionRect.h"
#include "physics.h"
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
	bool collisionToggle;
	D3DXVECTOR3 oldPos;
	bool colliding;
	int collData;
	physics * phys;

public:
	object()
	{
		plane = NULL;
		cube = NULL;
		collRect = NULL;
		targetCollRect = NULL;
		collisionToggle = true;
		colliding = false;
		collData = 0;
		phys = NULL;
	}
	object(dxManager* a_dxMgr, std::string imgFile)
	{
		plane = new XYPlane(a_dxMgr, imgFile);
		cube = NULL;
		collRect = new collisionRect();
		collRect->initRect(plane);
		collisionToggle = true;
		colliding = false;
		collData = 0;
		phys = NULL;
	}

	object(XYPlane * a_plane)
	{
		plane = a_plane;
		cube = NULL;
		collRect = new collisionRect();
		collRect->initRect(plane);
		collisionToggle = true;
		colliding = false;
		collData = 0;
		phys = NULL;
	}
	object(dxCube * a_cube)
	{
		plane = NULL;
		cube = a_cube;
		collRect = new collisionRect();
		collRect->initRect(a_cube);
		collisionToggle = true;
		colliding = false;
		collData = 0;
		phys = NULL;
	}

/**********************************************************************
* THE FOLLOWING CONSTRUCTORS MUST BE REMOVED
**********************************************************************/
	//// THIS CONSTRUCTOR IS DEPRECIATED
	//object(dxManager* a_dxMgr, std::string imgFile, std::string textFile)
	//{
	//	plane = new XYPlane(a_dxMgr, imgFile);
	//	cube = NULL;
	//	collRect = new collisionRect();
	//	collRect->initRect(plane);
	//	loadParametersFromTxtFile(textFile);
	//	collisionToggle = true;
	//	colliding = false;
	//	phys = NULL;
	//}
	//// THIS CONSTRUCTOR IS DEPRECIATED
	//object(XYPlane * a_plane, std::string textFile)
	//{
	//	plane = a_plane;
	//	cube = NULL;
	//	collRect = new collisionRect();
	//	collRect->initRect(plane);
	//	loadParametersFromTxtFile(textFile);
	//	collisionToggle = true;
	//	colliding = false;
	//	phys = NULL;
	//}
	//// THIS CONSTRUCTOR IS DEPRECIATED
	//object(dxCube * a_cube, std::string textFile)
	//{
	//	plane = NULL;
	//	cube = a_cube;
	//	collRect = new collisionRect();
	//	collRect->initRect(a_cube);
	//	loadParametersFromTxtFile(textFile);
	//	collisionToggle = true;
	//	colliding = false;
	//	phys = NULL;
	//}
/**********************************************************************
* THE PRECEDING CONSTRUCTORS MUST BE REMOVED
**********************************************************************/

	~object()
	{
		// call destructors
		// destroy plane
		if(plane)
		{
			plane->~XYPlane();
		}
		// destroy cube
		if(cube)
		{
			cube->~dxCube();
		}
		// destory the collision rect
		collRect->~collisionRect();

		// destroy the physics data
		phys->~physics();

		// handle pointers
		collRect = NULL;
		plane = NULL;
		cube = NULL;
		phys = NULL;
	}
	/********************************************************************************
	* loadParameters
	* loads the parameters for any object using a text file
	* instructions: send in a text file with the parameters in this order, separated by 
	* a space
	* x, y, z, width, height, rows, columns, left offset, top offset, right offset, 
	* bottom offset
	********************************************************************************/
	void loadParametersFromTxtFile(std::string filename)
	{
		std::fstream file(filename.c_str());
		D3DXVECTOR3 pos;
		float width, height, depth;
		int imageRows, imageColumns;
		FloatRect offset;
		// the size of the data we are going to create
		file >> pos.x >> pos.y >> pos.z >> width >> height >> depth >> imageRows >> imageColumns
			>> offset.left >> offset.top >> offset.right >> offset.bottom;
		if(plane)
		{
			plane->setParam(pos.x, pos.y, pos.z, width, height);
			plane->setImageRowsColumns(imageRows, imageColumns);
		}
		if(cube)
		{
			cube->setParam(pos.x, pos.y, pos.z, width, height, depth);
			cube->setImageRowsColumns(imageRows, imageColumns);
		}
		collRect->setOffset(&offset);
		collRect->update();
		recordPosition();
	}
	void loadParameters(float x, float y, float z, float width, float height, float depth,
		 int imageRows, int imageColumns, float leftOffset, float topOffset, float rightOffset,
		 float bottomOffset)
	{
		if(plane)
		{
			plane->setParam(x, y, z, width, height);
			plane->setImageRowsColumns(imageRows, imageColumns);
		}
		if(cube)
		{
			cube->setParam(x, y, z, width, height, depth);
			cube->setImageRowsColumns(imageRows, imageColumns);
		}
		collRect->setOffset(leftOffset, rightOffset, topOffset, bottomOffset);
		collRect->update();
		recordPosition();
	}
	void draw()
	{
		if(plane)
		{
			plane->draw();
		}
		if(cube)
		{
			cube->draw();
		}
	}
	/************************************************************************************
	* handleCollision
	* returns true if movement is valid, flase if movement is invalid and moves object back
	************************************************************************************/
	//bool handleCollision(float a_x, float a_y, float a_z)
	//{
	//	if(collisionToggle)
	//	{
	//		D3DXVECTOR3 pos; 
	//		if(plane)
	//		{
	//			pos = *plane->getPosition();
	//			plane->setPosition(a_x, a_y, a_z);
	//		}
	//		if(cube)
	//		{
	//			pos = *cube->getPosition();
	//			cube->setPosition(a_x, a_y, a_z);
	//		}
	//		collRect->update();
	//		if(collRect->collided(targetCollRect->getRect()))
	//		{
	//			if(plane)
	//			{
	//				plane->setPosition(pos);
	//			}
	//			if(cube)
	//			{
	//				cube->setPosition(pos);
	//			}
	//			collRect->update();
	//			return false;
	//		}
	//		return true;
	//	}
	//	else
	//	{
	//		if(plane)
	//		{
	//			plane->setPosition(a_x, a_y, a_z);
	//		}
	//		if(cube)
	//		{
	//			cube->setPosition(a_x, a_y, a_z);
	//		}
	//		collRect->update();
	//		return true;
	//	}
	//}

	void checkCollision()
	{
		if(!colliding)
		{
			colliding = collRect->collided(targetCollRect->getRect());
		}
		
		if(collRect->collided(targetCollRect->getRect()))
			collData |= collRect->classify(targetCollRect->getRect());
		//updatePhysics();
	}
	void updatePhysics()
	{
		if(phys)
		{
			//phys->onGroundOff();
			if(collData)
			{
				// check for top side collision
				if(collidingTop)
				{
					// if verticle collision occured, kill vertical velocity
					phys->killYVel();
				}
				// check for bottom side collision
				if(collidingBottom)
				{
					phys->onGroundOn();
					//// if verticle collision occured, kill vertical velocity
					//phys->killYVel();
					//// turn gravity off
					//phys->gravityOff();
					//// turn frick on if walking
					//phys->frictionOff();
					//if(!(phys->isWalking()))
					//{
					//	phys->frictionOn();
					//}
					//// allow jumping
					//phys->jumpingOn();
				}
				else
				{
					// check for left side collision
					if(collData & 1)
					{
						// if horizontal collision occured, kill horizontal velocity
						phys->killXVel();
					}
					// check for right side collision
					if((collData & (1<<1)) >> 1)
					{
						// if horizontal collision occured, kill horizontal velocity
						phys->killXVel();
					}
				}
				if(phys->isjumpingAllowed())
				{
					// check for left side collision
					if(collData & 1)
					{
						// if horizontal collision occured, kill horizontal velocity
						phys->killXVel();
					}
					// check for right side collision
					if((collData & (1<<1)) >> 1)
					{
						// if horizontal collision occured, kill horizontal velocity
						phys->killXVel();
					}
				}
			}
		}
	}
	void clear()
	{
		if(phys)
		{
			if(!colliding)
			{
				//phys->frictionOff();
				//if(!(phys->isWalking()))
				//{
				//	phys->frictionOn();
				//}
				//phys->onGroundOff();
				//phys->gravityOn();
				//phys->jumpingOff();
			}
		}
		colliding = false;
		collData = 0;
	}
	void recordPosition()
	{
		if(plane)
		{
			oldPos = *plane->getPosition();
		}
		if(cube)
		{
			oldPos = *cube->getPosition();
		}
	}
	bool isColliding(){return colliding;}

	collisionRect * getCollisionRect(){return collRect;}
	XYPlane * getXYPlane(){return plane;}
	dxCube * getDxCube(){return cube;}
	void setPosition(float a_x, float a_y, float a_z)
	{
		if(plane)
		{
			plane->setPosition(a_x, a_y, a_z);
		}
		if(cube)
		{
			cube->setPosition(a_x, a_y, a_z);
		}
		collRect->update();
	}
	void handleCollision()
	{
		// revert position
		if(plane)
		{
			plane->setPosition(oldPos);
		}
		if(cube)
		{
			cube->setPosition(oldPos);
		}
		collRect->update();
	}
	void setTargetCollision(collisionRect * a_collRect)
	{
		targetCollRect = a_collRect;
	}
	void toggleImage()
	{
		if(plane)
		{
			plane->toggleImage();
		}
		if(cube)
		{
			cube->toggleCube();
		}
	}
	void toggleCollision(){collisionToggle = !collisionToggle;}
	void collisionToggleOn(){collisionToggle = true;}
	void collisionToggleOff(){collisionToggle = false;}
	
	D3DXVECTOR3 * getPosition()
	{
		if(plane)
		{
			return plane->getPosition();
		}
		if(cube)
		{
			return cube->getPosition();
		}
		return NULL;
	}
	void togglePhysics()
	{
		if(phys)
		{
			phys->~physics();
			phys = NULL;
		}
		else
		{
			phys = new physics();
		}
	}
	physics * getPhysics(){return phys;}
};