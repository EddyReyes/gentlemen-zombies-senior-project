#include "player.h"

player::player()
{
	m_object = NULL;
	type = entityPlayer;
	timer = 0;
	armorBlink = false;
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

	/*switch(state)
	{
	case walkingRight:
		switch(sprites)
		{
		case playerSprite1:
			if(armor)
				m_object->setSprite(0, 0);
			else
				m_object->setSprite(2, 0);

			sprites = playerSprite2;
			break;
		case playerSprite2:
			if(armor)
				m_object->setSprite(0, 1);
			else
				m_object->setSprite(2, 1);

			sprites = playerSprite3;
			break;
		case playerSprite3:
			if(armor)
				m_object->setSprite(0, 2);
			else
				m_object->setSprite(2, 2);

			sprites = playerSprite4;
			break;
		case playerSprite4:
			if(armor)
				m_object->setSprite(0, 3);
			else
				m_object->setSprite(2, 3);

			sprites = playerSprite1;
			break;
		}
	case jumping:
		if(m_object->getPhysics()->getXVelocity() > 0)
		{
			if(armor)
				m_object->setSprite(0,4);
			else
				m_object->setSprite(2,4);
		}
		else if(m_object->getPhysics()->getXVelocity() < 0)
		{
			if(armor)
				m_object->setSprite(1,4);
			else
				m_object->setSprite(3,4);
		}
		break;
	
	case walkingLeft:
		switch(sprites)
		{
		case playerSprite1:
			if(armor)
				m_object->setSprite(1, 0);
			else
				m_object->setSprite(3, 0);

			sprites = playerSprite2;
			break;
		case playerSprite2:
			if(armor)
				m_object->setSprite(1, 1);
			else
				m_object->setSprite(3, 1);

			sprites = playerSprite3;
			break;
		case playerSprite3:
			if(armor)
				m_object->setSprite(1, 2);
			else
				m_object->setSprite(3, 2);

			sprites = playerSprite4;
			break;
		case playerSprite4:
			if(armor)
				m_object->setSprite(1, 3);
			else
				m_object->setSprite(3, 3);

			sprites = playerSprite1;
			break;
		}
		break;
	case idle:
		switch(sprites)
		{
		case playerSprite1:
			if(armor)
				m_object->setSprite(4, 0);
			else
				m_object->setSprite(5, 0);

			sprites = playerSprite2;
			break;
		case playerSprite2:
			if(armor)
				m_object->setSprite(4, 1);
			else
				m_object->setSprite(5, 1);

			sprites = playerSprite3;
			break;
		case playerSprite3:
			if(armor)
				m_object->setSprite(4, 2);
			else
				m_object->setSprite(5, 2);

			sprites = playerSprite4;
			break;
		case playerSprite4:
			if(armor)
				m_object->setSprite(4, 3);
			else
				m_object->setSprite(5, 3);

			sprites = playerSprite5;
			break;
		case playerSprite5:
			if(armor)
				m_object->setSprite(4, 4);
			else
				m_object->setSprite(5, 4);

			sprites = playerSprite1;
			break;
		}
		break;

	case dying:
		switch(sprites)
		{
		case playerSprite1:
			m_object->setSprite(6, 0);
			sprites = playerSprite2;
			break;
		case playerSprite2:
			m_object->setSprite(6, 1);
			sprites = playerSprite3;
			break;
		case playerSprite3:
			m_object->setSprite(6, 2);
			sprites = playerSprite4;
			break;
		case playerSprite4:
			m_object->setSprite(6, 3);
			sprites = playerSprite1;
			break;
		}
		break;
	case dead:
		switch(sprites)
		{
		case playerSprite1:
			m_object->setSprite(6, 4);
			sprites = playerSprite1;
			break;
		}
		break;
	}*/
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
					bounce();
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

	if(armorBlink)
	{
		armorTimeout -= timePassed;
		if(armorTimeout < 0) // armorTimeout has expired
		{
			armor = !armor;
			armorBlink = false;
			armorTimeout = 0;
		}
	}
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
void player::bounce()
{
	float deathXVel = m_object->getPhysics()->getXVelocity();
	float deathYVel = m_object->getPhysics()->getYVelocity();
	m_object->getPhysics()->setXVelocity(deathXVel * -3);
	m_object->getPhysics()->setYVelocity(10);
}

void player::removeArmor()
{
	if(armor)
	{
		if(!armorBlink)
		{
			armorBlink = true;
			armorTimeout = 2.0f;
		}
	}
}
void player::armorPickup()
{
	if(!armor)
	{
		if(!armorBlink)
		{
			armorBlink = true;
			armorTimeout = 2.0f;
		}
	}
}
bool player::getAmorBlink(){return armorBlink;}