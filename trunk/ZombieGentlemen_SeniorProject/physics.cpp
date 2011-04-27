#include "physics.h"

physics::physics()
{
	xVelocity = NULL;
	yVelocity = NULL;
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{
	xVelocity *= groundFriction;// * a_deltaTime;
	yVelocity += gravity * a_deltaTime;
}
void physics::updatePosition(D3DXVECTOR3 * pos)
{
	pos->x += xVelocity;
	pos->y += yVelocity;
}
void physics::killXVel(){xVelocity = 0;}
void physics::killYVel(){yVelocity = 0;}
