#pragma once
#include "XYPlane.h"
#include "dxManager.h"
#include "collisionRect.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

class object
{
protected:
	XYPlane *  image;
	collisionRect * collRect;
	bool collisionToggle;
	dxManager* dxMgr;
	float movement;

public:
	object(dxManager* a_dxMgr, std::string imgFile, char * textFile)
	{
		dxMgr = a_dxMgr;
		image = new XYPlane(dxMgr, imgFile);
		collRect = new collisionRect();
		collRect->initRect(image);
		loadParameters(textFile);
		movement = 0.005f;
	}
	~object()
	{
		image->~XYPlane();
		image = NULL;
		collRect->~collisionRect();
		collRect = NULL;
	}
	/********************************************************************************
	* loadParameters
	* loads the parameters for any object using a text file
	* instructions: send in a text file with the parameters in this order, separated by 
	* a space
	* x, y, z, width, height, rows, columns, left offset, top offset, right offset, 
	* bottom offset
	********************************************************************************/
	void loadParameters(char * filename)
	{
		std::fstream file(filename);
		D3DXVECTOR3 pos;
		float width, height;
		int imageRows, imageColumns;
		FloatRect offset;
		// the size of the data we are going to create
		file >> pos.x >> pos.y >> pos.z >> width >> height >> imageRows >> imageColumns
			>> offset.left >> offset.top >> offset.right >> offset.bottom;
		image->setParam(pos.x, pos.y, pos.z, width, height);
		image->setImageRowsColumns(imageRows, imageColumns);
		collRect->setOffset(&offset);
	}
	void loadParameters(float x, float y, float z, float width, float height,
		 int imageRows, int imageColumns, float leftOffset, float topOffset, float rightOffset,
		 float bottomOffset)
	{
		image->setParam(x, y, z, width, height);
		image->setImageRowsColumns(imageRows, imageColumns);
		collRect->setOffset(leftOffset, rightOffset, topOffset, bottomOffset);
	}
	void draw()
	{
		image->draw();
	}
	void handleCollision(float a_x, float a_y, float a_z, collisionRect * a_collRect)
	{
		D3DXVECTOR3 pos = *image->getPosition();
		image->setPosition(a_x, a_y, a_z);
		collRect->update();
		if(collRect->collided(a_collRect->getRect()))
		{
			image->setPosition(pos);
			collRect->update();
		}
	}
	collisionRect * getCollisionRect(){return collRect;}
	XYPlane * getXYPlane(){return image;}
	void setPosition(float a_x, float a_y, float a_z)
	{
		image->setPosition(a_x, a_y, a_z);
		collRect->update();
	}
	void toggleImage(){image->toggleImage();}
	void toggleCollision(){collisionToggle = !collisionToggle;}
};