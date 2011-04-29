#pragma once
#include "dxManager.h"

#define gravity -0.5f //-9.8f
#define groundFriction 0.99f

class physics
{
private:
	float xVelocity, yVelocity;
	bool friction, applyGravity;
	bool jumpingAllowed, walking;

public:
	// constructors
	physics();
	// destructor
	~physics();

	// member functions
	void update(float a_deltaTime);
	void updatePosition(D3DXVECTOR3 * pos);
	void killXVel();
	void killYVel();

	// mutators
	void setXVelocity(float a_xVelocity);
	void setYVelocity(float a_yVelocity);

	// accesors
	float getXVelocity(){return xVelocity;}
	float getYVelocity(){return yVelocity;}
	void frictionOn();
	void frictionOff();
	void gravityOn();
	void gravityOff();
	void jumpingOn();
	void jumpingOff();
	void walkingOn();
	void walkingOff();
	bool isWalking(){return walking;}
};