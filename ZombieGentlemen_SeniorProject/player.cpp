#include "player.h"

player::player()
{
	m_object = NULL;
	type = entityPlayer;
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
	bool spriteChange = false;
	if(!alive)
	{
		if(state != dead)
		{
			timer += timePassed;
			if(timer < 1)
			{
				if(state != dying && state != dead)
				{
					float deathXVel = m_object->getPhysics()->getXVelocity();
					float deathYVel = m_object->getPhysics()->getYVelocity();
					m_object->getPhysics()->setXVelocity(deathXVel * -3);
					m_object->getPhysics()->setYVelocity(10);
				}
				if(state != dying)
				{
					state = dying;
					spriteChange = true;
				}
			}
			else
			{
				if(state != dead)
				{
					state = dead;
					spriteChange = true;
				}
				timer = 0;
			}
		}
	}
	else if(m_object->getPhysics())
	{
		if(m_object->getPhysics()->isWalking())
		{
			if(m_object->getPhysics()->getXVelocity() > 0)
			{
				if(state != walkingRight)
				{
					state = walkingRight;
					spriteChange = true;
				}
			}
			else
			{
				if(state != walkingLeft)
				{
					state = walkingLeft;
					spriteChange = true;
				}
			}
		}
		else
		{
			if(state != idle)
			{
				state = idle;
				spriteChange = true;
			}
		}
		//if(!(m_object->getPhysics()->isOnGround()))
		if(m_object->getPhysics()->getYVelocity() > 0)
		{
			if(state != jumping)
			{
				state = jumping;
				spriteChange = true;
			}
		}
	}
	if(spriteChange)
		animate();
}

void player::reset()
{
	timer = 0;
	state = idle;
	m_object->setSprite(0,0);
	m_object->getCollHistory()->resetList();
	alive = true;
	armor = false;
}