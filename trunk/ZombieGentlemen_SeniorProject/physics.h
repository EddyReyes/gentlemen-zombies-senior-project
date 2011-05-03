#pragma once
#include "dxManager.h"

#define gravity -50.0f
#define groundFriction 0.8f


class physics
{
private:
	float xVelocity, yVelocity, time;
	bool friction, hitTop;
	bool jumpingAllowed, walking, onGround, rightMove, leftMove;
	float jumpLag;

public:
	// constructors
	physics();
	// destructor
	~physics();

	// member functions
	void update(float a_deltaTime);
	void updatePosition(D3DXVECTOR3 * pos);
	void updateMovePermissions();
	void killXVel();
	void killYVel();

	// mutators
	void setXVelocity(float a_xVelocity);
	void setYVelocity(float a_yVelocity);

	// accesors
	float getXVelocity(){return xVelocity;}
	float getYVelocity(){return yVelocity;}

	// flag accessors
	bool hasGravity();
	bool isWalking(){return walking;}
	bool isjumpingAllowed(){return jumpingAllowed;}
	bool canMoveLeft(){return leftMove;}
	bool canMoveRight(){return rightMove;}
	bool isOnGround(){return onGround;}

	// flag mutators
	void frictionOn();
	void frictionOff();
	void gravityOn();
	void gravityOff();
	void jumpingOn();
	void jumpingOff();
	void walkingOn();
	void walkingOff();
	void onGroundOn(){onGround = true;}
	void onGroundOff(){onGround = false;}
};