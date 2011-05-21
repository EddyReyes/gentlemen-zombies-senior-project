#include "physics.h"

physics::physics()
{
	gravity =  -50.0f;
	groundFriction = 0.8f;

	xVelocity = NULL;
	yVelocity = NULL;
	friction = false;
	jumpingAllowed = true;
	walking = false;
	onGround = false;
	leftMove = true;
	rightMove = true;
	jumpLag = 0;
	time = 0;
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{
	time = a_deltaTime;
	if(onGround)
	{
		if(!walking)
		{
			xVelocity *= groundFriction;
		}
		if(xVelocity < 0.001 && xVelocity > -0.001)
			xVelocity = 0;

		// kill yVelocity
		yVelocity = 0;
		// reset hit top flag
		hitTop = false;
		// allow jumping
		jumpingAllowed = true;
	}
	else
	{
		// apply gravity
		yVelocity += gravity * a_deltaTime;
		xVelocity *= 0.9f;
		// turn friction off
		friction = false;
		// do not allow jumping
		jumpingAllowed = false;
	}
}
void physics::updatePosition(D3DXVECTOR3 * pos)
{
	pos->x += xVelocity * time;
	pos->y += yVelocity * time;
}

void physics::updateMovePermissions()
{
	if(onGround)
	{
		if(xVelocity >= 0)
			leftMove = true;
		if(xVelocity <= 0)
			rightMove = true;
	}
	if(!leftMove && !rightMove)
	{
		leftMove = true;
		rightMove = true;
	}
}

void physics::setXVelocity(float a_xVelocity){xVelocity = a_xVelocity;}
void physics::setYVelocity(float a_yVelocity)
{
	if(jumpingAllowed)
		yVelocity = a_yVelocity;
}
void physics::killXVel()
{
	if(xVelocity < 0)
		leftMove = false;
	if(xVelocity > 0)
		rightMove = false;
	if(!hitTop)
		xVelocity = xVelocity * -0.1f;
	else
	{
		xVelocity = 0;
	}
}
void physics::killYVel()
{
	if(yVelocity > 0)
		hitTop = true;
	yVelocity = 0;
}

void physics::setGravity(float a_gravity){gravity = a_gravity;}
void physics::setGroundFriction(float a_friction){groundFriction = a_friction;}

void physics::frictionOn(){friction = true;}
void physics::frictionOff(){friction = false;}
void physics::jumpingOn(){jumpingAllowed = true;}
void physics::jumpingOff(){jumpingAllowed = false;}
void physics::walkingOn(){walking = true;}
void physics::walkingOff(){walking = false;}