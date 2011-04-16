#include "physicsObject.h"

physicsObject::physicsObject()
{
	physObject = NULL;
	xVelocity = NULL;
	yVelocity = NULL;
	xAcceleration = NULL;
	yAcceleration = NULL;
	gravity = NULL;
	sharingObject = false;
}
physicsObject::physicsObject(object * a_object)
{
	physObject = a_object;
	xVelocity = NULL;
	yVelocity = NULL;
	xAcceleration = NULL;
	yAcceleration = NULL;
	gravity = NULL;
	sharingObject = true;
}
physicsObject::physicsObject(dxManager* a_dxMgr, std::string imgFile, char * textFile)
{
	physObject = new object(a_dxMgr, imgFile, textFile);
	xVelocity = NULL;
	yVelocity = NULL;
	xAcceleration = NULL;
	yAcceleration = NULL;
	gravity = NULL;
	sharingObject = false;
}
physicsObject::~physicsObject()
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