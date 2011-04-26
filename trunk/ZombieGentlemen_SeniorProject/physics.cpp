#include "physics.h"

physics::physics()
{
	physObject = NULL;
	xVelocity = NULL;
	yVelocity = NULL;
}
physics::physics(object * a_object)
{
	physObject = a_object;
	xVelocity = NULL;
	yVelocity = NULL;
}
physics::~physics(){}
void physics::update(float a_deltaTime)
{
	xVelocity *= groundFriction * deltaTime;
	yVelocity += gravity * deltaTime;
}
void physics::updatePosition()
{
	physObject->recordPosition();
	D3DXVECTOR3 * pos = physObject->getPosition();
	pos->x += xVelocity;
	pos->y += yVelocity;
	physObject->getCollisionRect()->update();
}
void physics::killXVel(){xVelocity = 0;}
void physics::killYVel(){yVelocity = 0;}
