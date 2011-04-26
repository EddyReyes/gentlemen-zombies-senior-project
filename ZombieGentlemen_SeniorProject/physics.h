#pragma once
#include "object.h"

#define gravity 0.001f //-9.8f
#define groundFriction 0.008f

class physics
{
private:
	object * physObject;
	float xVelocity, yVelocity;
	float deltaTime;

public:
	// constructors
	physics();
	physics(object * a_object);
	// destructor
	~physics();

	// member functions
	void setObject(object * a_object){physObject = a_object;}
	void update(float a_deltaTime);
	void updatePosition();
	void killXVel();
	void killYVel();

	// mutators
	void setXVelocity(float a_xVelocity){xVelocity = a_xVelocity;}
	void setYVelocity(float a_yVelocity){yVelocity = a_yVelocity;}

	// accesors
	float getXVelocity(){return xVelocity;}
	float getYVelocity(){return yVelocity;}
};