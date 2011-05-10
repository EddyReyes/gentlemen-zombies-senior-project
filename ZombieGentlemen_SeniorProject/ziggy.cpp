#include "ziggy.h"

/***********************************************************************
 * Makes the ziggy enemy(bird/fish) fly or swim in a wave like pattern * 
 ***********************************************************************/
void ziggy::load()
{
	
}
void ziggy::update(float timePassed)
{
	/***************************************************************** 
	 * Will update ziggy's position per frame and as soon            *
	 * as the enemy flys or swims from one side to the other         *
	 *****************************************************************/
	// the following animations are simplified versions
	switch(state)
	{
	case fly1:
		m_object->setSprite(0,0);
		break;
	case fly2:
		m_object->setSprite(0,1);
		break;
	case fly3:
		m_object->setSprite(0,2);
		break;
	case deadZiggy:
		m_object->setSprite(0,3);
		break;
	}

	D3DXVECTOR3 * pos;
	pos = m_object->getPosition();
	pos->x += 0.5f * timePassed;
	//here I need physics to drop ziggy, then make him accelerate up
	//?????????
	//ziggy will accelerate up for a time, then fall a certain time
	//repeat the process
	//m_object->getPhysics()->getYVelocity();
	m_object->getCollisionRect()->update();
}