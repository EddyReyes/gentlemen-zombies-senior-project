#include "physics.h"

physics::physics()
{
	xVelocity = NULL;
	yVelocity = NULL;
	friction = false;
	jumpingAllowed = true;
	walking = false;
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{
	if(!walking)
	{
		if(friction)
		{
			xVelocity *= groundFriction;
		}
	}
	if(xVelocity < 0.0001 && xVelocity > -0.0001)
		xVelocity = 0;
	if(applyGravity)
	{
		yVelocity += gravity * a_deltaTime;
	}
}
void physics::updatePosition(D3DXVECTOR3 * pos)
{
	pos->x += xVelocity;
	pos->y += yVelocity;
}

void physics::setXVelocity(float a_xVelocity){xVelocity = a_xVelocity;}
void physics::setYVelocity(float a_yVelocity)
{
	if(jumpingAllowed)
		yVelocity = a_yVelocity;
}
void physics::killXVel(){xVelocity = 0;}
void physics::killYVel(){yVelocity = 0;}
void physics::frictionOn(){friction = true;}
void physics::frictionOff(){friction = false;}
void physics::gravityOn(){applyGravity = true;}
void physics::gravityOff(){applyGravity = false;}
void physics::jumpingOn(){jumpingAllowed = true;}
void physics::jumpingOff(){jumpingAllowed = false;}
void physics::walkingOn(){walking = true;}
void physics::walkingOff(){walking = false;}
