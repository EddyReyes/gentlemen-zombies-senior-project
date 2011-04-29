#pragma once
#include "dxManager.h"

#define gravity -0.5f //-9.8f
#define groundFriction 0.97f

class physics
{
private:
	float xVelocity, yVelocity;
	bool friction, applyGravity;
	bool jumpingAllowed, walking, onGround;

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
	bool hasGravity();
	bool isWalking(){return walking;}


	bool isOnGround(){return onGround;}
	void onGroundOn(){onGround = true;}
	void onGroundOff(){onGround = false;}
};