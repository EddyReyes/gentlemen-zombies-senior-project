#include "physics.h"

physics::physics()
{
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
			xVelocity *= groundFriction ;
		}
		if(xVelocity < 0.001 && xVelocity > -0.001)
			xVelocity = 0;

		// kill yVelocity
		yVelocity = 0;
		// allow jumping
		

		hitTop = false;
			jumpingAllowed = true;
	
	/*	if(xVelocity > 0)
			leftMove = true;
		if(xVelocity < 0)
			rightMove = true;*/
	}
	else
	{
		// apply gravity
		yVelocity += gravity * a_deltaTime;
		// turn friction off
		friction = false;
		// do not allow jumping
		jumpingAllowed = false;

	/*	leftMove = true;
		rightMove = true;*/
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

void physics::setXVelocity(float a_xVelocity)
{
	/*if(a_xVelocity < 0 && leftMove && onGround)
		xVelocity = a_xVelocity;
	if(a_xVelocity > 0 && rightMove && onGround)
		xVelocity = a_xVelocity;
	if(a_xVelocity == 0);*/
		xVelocity = a_xVelocity;

}
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
		xVelocity = xVelocity * -0.1 ;
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
void physics::frictionOn(){friction = true;}
void physics::frictionOff(){friction = false;}
void physics::jumpingOn(){jumpingAllowed = true;}
void physics::jumpingOff(){jumpingAllowed = false;}
void physics::walkingOn(){walking = true;}
void physics::walkingOff(){walking = false;}
