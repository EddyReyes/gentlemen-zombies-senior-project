#pragma once
#include "dxManager.h"

// standard gravity and ground friction
//#define gravity -50.0f
//#define groundFriction 0.8f

class physics
{
private:
	float xVelocity, yVelocity, time;
	bool friction, hitTop;
	bool jumpingAllowed, walking, onGround, rightMove, leftMove;
	float jumpLag;
	float gravity, groundFriction;

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
	void setGravity(float a_gravity);
	void setGroundFriction(float a_friction);

	// accesors
	float getXVelocity(){return xVelocity;}
	float getYVelocity(){return yVelocity;}
	float getGravity(){return gravity;}
	float getGroundFriction(){return groundFriction;}

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