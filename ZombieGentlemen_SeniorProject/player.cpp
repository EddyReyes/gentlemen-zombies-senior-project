#include "player.h"

player::player()
{
	m_object = NULL;
	type = playerEntity;
	timer = 0;
}
player::~player()
{

}

void player::move(float x, float y)
{
	if(alive)
	{
		m_object->getPhysics()->walkingOn();
		if(x)
			if((x < 0 && m_object->getPhysics()->canMoveLeft())
				|| (x > 0 && m_object->getPhysics()->canMoveRight()))
				m_object->getPhysics()->setXVelocity(x);
		if(y)
			m_object->getPhysics()->setYVelocity(y);
	}
}

void player::animate()
{
	// the following animations are simplified versions
	switch(state)
	{
	case idle:
		m_object->setSprite(0,0);
		break;
	case walkingRight:
		m_object->setSprite(0,1);
		break;
	case walkingLeft:
		m_object->setSprite(0,2);
		break;
	case jumping:
		m_object->setSprite(0,3);
		break;
	case dying:
		m_object->setSprite(0,4);
		break;
	case dead:
		m_object->setSprite(0,5);
		break;

	}
}

void player::update(float timePassed)
{
	if(!alive)
	{
		if(state != dead)
		{
			timer += timePassed;
			if(timer < 2)
			{
				if(state != dying && state != dead)
				{
					float deathXVel = m_object->getPhysics()->getXVelocity();
					float deathYVel = m_object->getPhysics()->getYVelocity();
					m_object->getPhysics()->setXVelocity(deathXVel * -2);
					m_object->getPhysics()->setYVelocity(deathYVel * -2);
				}
				state = dying;
			}
			else
			{
				state = dead;
				timer = 0;
			}
		}
	}
	else if(m_object->getPhysics())
	{
		if(m_object->getPhysics()->isWalking())
		{
			if(m_object->getPhysics()->getXVelocity() > 0)
				state = walkingRight;
			else
				state = walkingLeft;
		}
		else
		{
			state = idle;
		}
		//if(!(m_object->getPhysics()->isOnGround()))
		if(m_object->getPhysics()->getYVelocity() > 0)
		{
			state = jumping;
		}
	}
	animate();
}
void player::displayLoadError()
{
	MessageBox(NULL, "Player parameter file is empty", "Player Error", MB_OK);
}