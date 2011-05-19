#include "ziggy.h"

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
	pos->x += 0.5f * timePassed;
	if (pos->x > 0)
	{
		m_object->getPhysics()->getYVelocity();
		for (int i = 0; i < 30; i++)
		{
			m_object->getPhysics()->setYVelocity(2.0f);
		}
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
}
void ziggy::reset()
{
	state = fly1;
	alive = true;
	armor = false;
}