#include "physics.h"

physics::physics()
{
	xVelocity = NULL;
	yVelocity = NULL;
	friction = false;
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{
	if(friction)
	{
		xVelocity *= groundFriction;
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
void physics::killXVel(){xVelocity = 0;}
void physics::killYVel(){yVelocity = 0;}
void physics::frictionOn(){friction = true;}
void physics::frictionOff(){friction = false;}
void physics::gravityOn(){applyGravity = true;}
void physics::gravityOff(){applyGravity = false;}
