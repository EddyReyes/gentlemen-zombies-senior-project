#include "ziggy.h"

ziggy::ziggy()
{
	m_object = NULL;
	state = fly1;
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

	// accelerate to the left
	m_object->getPhysics()->setXVelocity(-3.0f);
	
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
}
void ziggy::reset()
{
	state = fly1;
	alive = true;
	armor = false;
}