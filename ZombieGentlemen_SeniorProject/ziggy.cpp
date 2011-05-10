#include "ziggy.h"
#include "dxManager.h"
#include "CustomVertex.h"
/***********************************************************************
 * Makes the ziggy enemy(bird/fish) fly or swim in a wave like pattern * 
 ***********************************************************************/
void ziggy::load()
{
	//will load the ziggy flying enemy in game maps
	m_object->setSprite(0, 1);
	m_object->getCollData();
	m_object->checkCollision();

}
void ziggy::update(float timePassed)
{
	/***************************************************************** 
	 * Will update ziggy's position per frame and as soon            *
	 * as the enemy flys or swims from one side to the other         *
	 *****************************************************************/
	D3DXVECTOR3 * pos;
	pos = m_object->getPosition();
	if ( pos->x < 800)
	pos->x += 0.5f * timePassed;
	//here I need physics to drop ziggy, then make him accelerate up
	else if ( pos->x > 800 )
	pos->x *= -0.5f * timePassed;
	//here I need physics to drop ziggy, then make him accelerate up
	//?????????
	m_object->getCollisionRect()->update();
}