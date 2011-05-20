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
	D3DXVECTOR3 * pos;
	pos = m_object->getPosition();
	
	pos->x -= 0.5f * timePassed;
	
	//figure out y movement when time passes with x
	//if (pos->y > 0)
	/*{
		m_object->getPhysics()->onGroundOn();
		pos->y -= 0.2f * timePassed; 
	}*/
	if (m_object->getPosition()->y <= defaultPos.y)
	{
		m_object->getPhysics()->onGroundOn();
		m_object->getPhysics()->setYVelocity(12.0f);
	}
	if (m_object->getPhysics()->getYVelocity() > 0)
	{
		state = fly3;
	}
	else if (m_object->getPhysics()->getYVelocity() < 0)
	{
		state = fly1;	
	}
	else if (m_object->getPhysics()->getYVelocity() == 0)
	{
		state = fly2;
	}


	m_object->getCollisionRect()->update();	
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