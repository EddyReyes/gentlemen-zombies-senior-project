#pragma once
#include "object.h"

class physicsObject
{
private:
	object * physObject;
	float xVelocity, yVelocity, xAcceleration, yAcceleration;
	float gravity;
	bool sharingObject;

public:
	physicsObject()
	{
		physObject = NULL;
		xVelocity = NULL;
		yVelocity = NULL;
		xAcceleration = NULL;
		yAcceleration = NULL;
		gravity = NULL;
		sharingObject = false;
	}
	physicsObject(object * a_object)
	{
		physObject = a_object;
		xVelocity = NULL;
		yVelocity = NULL;
		xAcceleration = NULL;
		yAcceleration = NULL;
		gravity = NULL;
		sharingObject = true;
	}
	physicsObject(dxManager* a_dxMgr, std::string imgFile, char * textFile)
	{
		physObject = new object(a_dxMgr, imgFile, textFile);
		xVelocity = NULL;
		yVelocity = NULL;
		xAcceleration = NULL;
		yAcceleration = NULL;
		gravity = NULL;
		sharingObject = false;
	}
	~physicsObject()
	{
		if(!sharingObject)
		{
			if(physObject)
			{
				physObject->~object();
				physObject = NULL;
			}
		}
	}
	void setObject(object * a_object){physObject = a_object;}
	void setXVelocity(float a_xVelocity){xVelocity = a_xVelocity;}
	void setYVelocity(float a_yVelocity){yVelocity = a_yVelocity;}
	void setXAcceleration(float a_xAcceleration){xAcceleration = a_xAcceleration;}
	void setYAcceleration(float a_yAcceleration){yAcceleration = a_yAcceleration;}
	void setGravity(float a_gravity){gravity = a_gravity;}

	float getXVelocity(){return xVelocity;}
	float getYVelocity(){return yVelocity;}
	float getXAcceleration(){return xAcceleration;}
	float getYAcceleration(){return yAcceleration;}
	float getGravity(){return gravity;}

};