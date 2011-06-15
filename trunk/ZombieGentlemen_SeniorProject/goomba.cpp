#include "goomba.h"

goomba::goomba()
{
	type = entityGoomba;
	m_object = NULL;
	state = goombaWalkLeft;
	sprite = 0;
	timer = 0;
	flipTimer = 0;
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
	timer += timePassed;
	if(flipTimer > 0)
		flipTimer -= timePassed;
	bool animateFlag = false;
	if(m_object->getPhysics())
	{

		//check if goomba has reached a corner and turn around
		int collData = m_object->getCollData();
		//if goomba reaches right side of ledge, turn around
		if(collidingLeft && !(collidingRight) && collidingBottom)
		{
			state = goombaWalkLeft;
			animateFlag = true;
		}
		// if goomba reaches left side of ledge turn around
		if(collidingRight && !(collidingLeft) && collidingBottom)
		{
			state = goombaWalkRight;
			animateFlag = true;
		}
		// if goomba hits a wall
		if(collidingRight && collidingLeft && collidingTop && collidingBottom)
		{
			// if goomba was previously walking left switch to right, and vise versa
			if(state == goombaWalkRight)
			{
				state = goombaWalkLeft;
				animateFlag = true;
			}
			else if(state == goombaWalkLeft)
			{
				state = goombaWalkRight;
				animateFlag = true;
			}
		}

		// apply movement
		switch(state)
		{
		case goombaWalkLeft: m_object->getPhysics()->setXVelocity(-3.0f);
			break;
		case goombaWalkRight: m_object->getPhysics()->setXVelocity(3.0f);
			break;
		}
	}
	if(timer >= 0.3f || animateFlag)
	{
		animate();
		timer = 0;
	}
}
void goomba::animate()
{
	switch(state)
	{
	case goombaWalkLeft:
		m_object->setSprite(0, sprite);
		switch(sprite)
		{
		case 0: sprite = 1;
			break;
		case 1: sprite = 0;
			break;
		}
		break;
	case goombaWalkRight:
		m_object->setSprite(1, sprite);
		switch(sprite)
		{
		case 0: sprite = 1;
			break;
		case 1: sprite = 0;
			break;
		}
		break;
	}
}

void goomba::flip()
{
	if(flipTimer <= 0)
	{
		switch(state)
		{
		case goombaWalkLeft:
			state = goombaWalkRight;
			break;
		case goombaWalkRight:
			state = goombaWalkLeft;
			break;
		}
		animate();
		flipTimer = 0.1f;
	}
}
void goomba::reset()
{
	state = goombaWalkLeft;
	alive = true;
	armor = false;
}
void goomba::setDirection(char dir)
{
	switch(dir)
	{
	case 'l': state = goombaWalkLeft;
		break;
	case 'r': state = goombaWalkRight;
		break;
	default: 
		break;
	}
}