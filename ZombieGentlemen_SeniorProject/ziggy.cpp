#include "ziggy.h"

ziggy::ziggy()
{
	m_object = NULL;
	state = fly1;
	direction = ziggyLeft;
	time = 0;
}
ziggy::~ziggy()
{
	//does nothing, destruction happens in object manager
}
/***********************************************************************
 * Makes the ziggy enemy(bird/fish) fly or swim in a wave like pattern * 
 ***********************************************************************/
void ziggy::update(float timePassed)
{
	/***************************************************************** 
	 * Will update ziggy's position per frame and as soon            *
	 * as the enemy flys or swims from one side to the other         *
	 *****************************************************************/

	time += timePassed;

	//check if goomba has reached a corner and turn around
	int collData = m_object->getCollData();
	// if ziggy hits a wall
	if(collidingBottom)
	{
		// if ziggy crashes into somthing jump away from it
		m_object->getPhysics()->jumpingOn();
		m_object->getPhysics()->onGroundOff();
		m_object->getPhysics()->setYVelocity(5.0f);
	}
	if(collidingRight || collidingLeft)
	{
		// if ziggy was previously flying left switch to right, and vise versa
		if(direction == ziggyRight)
			direction = ziggyLeft;
		else if(direction == ziggyLeft)
			direction = ziggyRight;
	}


	switch(direction)
	{
	case ziggyLeft:
		// accelerate to the left
		m_object->getPhysics()->setXVelocity(-3.0f);

		break;
	case ziggyRight:
		// accelerate to the right
		m_object->getPhysics()->setXVelocity(3.0f);
		break;
	}


	
	// fly up wen it hits its spawn points Y coord
	if (m_object->getPosition()->y <= defaultPos.y)
	{
		m_object->getPhysics()->jumpingOn();
		m_object->getPhysics()->setYVelocity(7.0f);
	}

	if (m_object->getPhysics()->getYVelocity() > 0)
	{
		state = fly3;
	}
	else if (m_object->getPhysics()->getYVelocity() < 0)
	{
		state = fly1;
		time = 0;
	}
	else if (m_object->getPhysics()->getYVelocity() == 0)
	{
		state = fly2;
	}

	if(time >= 0.3)
	{
		if(state == fly3)
			state = fly2;
	}

	animate();
}
void ziggy::animate()
{
	switch(direction)
	{
	case ziggyLeft:

		// the following animations are simplified versions
		switch(state)
		{
		case fly1:
			m_object->setSprite(0, 0);
			state = fly1;
			break;
		case fly2:
			m_object->setSprite(0, 1);
			state = fly2;
			break;
		case fly3:
			m_object->setSprite(0, 2);
			state = fly3;
			break;
		}
		break;
	case ziggyRight:
		// the following animations are simplified versions
		switch(state)
		{
		case fly1:
			m_object->setSprite(1, 2);
			state = fly1;
			break;
		case fly2:
			m_object->setSprite(1, 1);
			state = fly2;
			break;
		case fly3:
			m_object->setSprite(1, 0);
			state = fly3;
			break;
		}
		break;
	}
}
void ziggy::reset()
{
	state = fly1;
	alive = true;
	armor = false;
}
void ziggy::flip()
{
	// ziggys flip automajically 
}