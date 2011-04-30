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
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{

	

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
		// allow jumping
		jumpingAllowed = true;

		if(xVelocity > 0)
			leftMove = true;
		if(xVelocity < 0)
			rightMove = true;

	}
	else
	{
		// apply gravity
		yVelocity += gravity * a_deltaTime;
		// turn friction off
		friction = false;
		// do not allow jumping
		jumpingAllowed = false;

		leftMove = true;
		rightMove = true;
	}
}
void physics::updatePosition(D3DXVECTOR3 * pos)
{
	pos->x += xVelocity;
	pos->y += yVelocity;
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
	xVelocity = 0;
}
void physics::killYVel(){yVelocity = 0;}
void physics::frictionOn(){friction = true;}
void physics::frictionOff(){friction = false;}
void physics::gravityOn(){applyGravity = true;}
void physics::gravityOff(){applyGravity = false;}
bool physics::hasGravity(){return applyGravity;}
void physics::jumpingOn(){jumpingAllowed = true;}
void physics::jumpingOff(){jumpingAllowed = false;}
void physics::walkingOn(){walking = true;}
void physics::walkingOff(){walking = false;}
