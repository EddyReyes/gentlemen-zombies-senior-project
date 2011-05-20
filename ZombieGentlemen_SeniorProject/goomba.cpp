#include "goomba.h"

goomba::goomba()
{
	type = entityGoomba;
	m_object = NULL;
	state = goombaWalkLeft;
}

goomba::~goomba()
{
	// destruction of the goomba object will happen in the object manager
}
/**
*uses states to determine which direction its move and also what to do
*should change direction when collision with a wall happens
**/
void goomba::update(float timePassed)
{
	if(m_object->getPhysics())
	{

		//check if goomba has reached a corner and turn around
		int collData = m_object->getCollData();
		//if goomba reaches right side of ledge, turn around
		if(collidingLeft && !(collidingRight) && collidingBottom)
		{
			state = goombaWalkLeft;
		}
		// if goomba reaches left side of ledge turn around
		if(collidingRight && !(collidingLeft) && collidingBottom)
		{
			state = goombaWalkRight;
		}
		// if goomba hits a wall
		if(collidingRight && collidingLeft && collidingTop && collidingBottom)
		{
			// if goomba was previously walking left switch to right, and vise versa
			if(state == goombaWalkRight)
				state = goombaWalkLeft;
			else if(state == goombaWalkLeft)
				state = goombaWalkRight;
		}

		// apply movement
		switch(state)
		{
		case goombaWalkLeft: m_object->getPhysics()->setXVelocity(-3.0f);
			break;
		case goombaWalkRight: m_object->getPhysics()->setXVelocity(3.0f);
			break;
		case goombaDead: m_object->getPhysics()->setXVelocity(0);
			break;
		}
	}
}
void goomba::animate()
{

}
void goomba::reset()
{
	state = goombaWalkLeft;
	alive = true;
	armor = false;
}