#include "player.h"

player::player()
{
	m_object = NULL;
}
player::~player()
{

}

void player::move(float x, float y)
{
	m_object->getPhysics()->setXVelocity(x);
	m_object->getPhysics()->setYVelocity(y);
}

void player::animate()
{
	// the following animations are simplified versions
	switch(state)
	{
	case idle:
		m_object->setSprite(0,0);
		break;
	case walking:
		m_object->setSprite(0,1);
		break;
	case jumping:
		m_object->setSprite(0,2);
		break;
	case dead:
		m_object->setSprite(0,4);
		break;
	}
}

void player::update(float timePassed)
{
	if(m_object->getPhysics())
	{
		if(m_object->getPhysics()->isWalking())
		{
			state = walking;
		}
		else
		{
			state = idle;
		}
		if(!(m_object->getPhysics()->isOnGround()))
		{
			state = jumping;
		}
		if(!alive)
		{
			state = dead;
		}
	}
	animate();
}
