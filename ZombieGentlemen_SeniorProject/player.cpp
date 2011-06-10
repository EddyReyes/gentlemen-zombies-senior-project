#include "player.h"

player::player()
{
	m_object = NULL;
	soundMgr = NULL;
	type = entityPlayer;
	timer = 0;
	randomIdle = 0;
	jumpCounter = 0;
	armorBlink = false;
	keyBlink =false;
	hasKey = false;
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
			{
				m_object->getPhysics()->setXVelocity(x);
				soundMgr->playSound(soundWalk);
			}
		if(y)
		{
			m_object->getPhysics()->setYVelocity(y);
			if(m_object->getPhysics()->isjumpingAllowed())
			{
				jumpCounter++;
				if(jumpCounter >= jumpInterval)
				{
					if(armor)
						soundMgr->playSound(soundArmorJump2);
					else
						soundMgr->playSound(soundJump2);
					jumpCounter = 0;
					jumpInterval = 4 + rand()%4;
				}
				else
				{
					if(armor)
						soundMgr->playSound(soundArmorJump1);
					else
						soundMgr->playSound(soundJump1);
				}
			}
		}
	}
}

void player::animate()
{
	switch(state)
	{
	case walkingRight:
		switch(sprites)
		{
		case playerSprite1:
			if(!armor)
				m_object->setSprite(0, 0);
			else
				m_object->setSprite(2, 0);

			sprites = playerSprite2;
			break;
		case playerSprite2:
			if(!armor)
				m_object->setSprite(0, 1);
			else
				m_object->setSprite(2, 1);

			sprites = playerSprite3;
			break;
		case playerSprite3:
			if(!armor)
				m_object->setSprite(0, 2);
			else
				m_object->setSprite(2, 2);

			sprites = playerSprite4;
			break;
		case playerSprite4:
			if(!armor)
				m_object->setSprite(0, 3);
			else
				m_object->setSprite(2, 3);

			sprites = playerSprite1;
			break;
		}
		break;


	case walkingLeft:
		switch(sprites)
		{
		case playerSprite1:
			if(!armor)
				m_object->setSprite(1, 0);
			else
				m_object->setSprite(3, 0);

			sprites = playerSprite2;
			break;
		case playerSprite2:
			if(!armor)
				m_object->setSprite(1, 1);
			else
				m_object->setSprite(3, 1);

			sprites = playerSprite3;
			break;
		case playerSprite3:
			if(!armor)
				m_object->setSprite(1, 2);
			else
				m_object->setSprite(3, 2);

			sprites = playerSprite4;
			break;
		case playerSprite4:
			if(!armor)
				m_object->setSprite(1, 3);
			else
				m_object->setSprite(3, 3);

			sprites = playerSprite1;
			break;
		}
		break;

	case jumping:
		if(m_object->getPhysics()->getXVelocity() > 0)
		{
			if(!armor)
				m_object->setSprite(0,4);
			else
				m_object->setSprite(2,4);
		}
		else if(m_object->getPhysics()->getXVelocity() < 0)
		{
			if(!armor)
				m_object->setSprite(1,4);
			else
				m_object->setSprite(3,4);
		}
		break;

	case idle:
		if(randomIdle <= 0)
		{
			randomIdle = 1 + ( (float)rand( ) / (float)RAND_MAX ) * 3;
			sprites = (enum playerSprite)(rand() % 5);
		}
		switch(sprites)
		{
		case playerSprite1:
			if(!armor)
				m_object->setSprite(4, 0);
			else
				m_object->setSprite(5, 0);
			break;
		case playerSprite2:
			if(!armor)
				m_object->setSprite(4, 1);
			else
				m_object->setSprite(5, 1);
			break;
		case playerSprite3:
			if(!armor)
				m_object->setSprite(4, 2);
			else
				m_object->setSprite(5, 2);
			break;
		case playerSprite4:
			if(!armor)
				m_object->setSprite(4, 3);
			else
				m_object->setSprite(5, 3);
			break;
		case playerSprite5:
			if(!armor)
				m_object->setSprite(4, 4);
			else
				m_object->setSprite(5, 4);
			break;
		}
		break;

	case dying:
		if(timer < 0.1f)
			sprites = playerSprite1;
		else if(timer < 0.2f)
			sprites = playerSprite2;
		else if(timer < 0.5f)
			sprites = playerSprite3;
		else sprites = playerSprite4;

		switch(sprites)
		{
		case playerSprite1:
			m_object->setSprite(6, 0);
			break;
		case playerSprite2:
			m_object->setSprite(6, 1);
			break;
		case playerSprite3:
			m_object->setSprite(6, 2);
			break;
		case playerSprite4:
			m_object->setSprite(6, 3);
			break;
		}
		break;

	case dead:
		m_object->setSprite(6, 4);
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
			if(timer < 1.2f)
			{
				if(state != dying && state != dead)
				{
					bounce();
				}
				if(state != dying)
				{
					state = dying;
					soundMgr->playSound(soundDeath1 + (rand()%3));
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
	else
	{
		timer += timePassed;
		if(randomIdle > 0)
		{
			randomIdle -= timePassed;
		}
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
		if(m_object->getPhysics()->getYVelocity() > 0)
		{
			if(state != jumping)
			{
				state = jumping;
				spriteChange = true;
			}
		}
	}
	if(spriteChange || timer >= 0.15f)
	{
		if(spriteChange)
			sprites = playerSprite1;
		animate();
		if(state != dying)
			timer = 0;
	}

	if(armorBlink)
	{
		armorTimeout -= timePassed;
		if(armorTimeout < 0) // armorTimeout has expired
		{
			if(armorLoss)
				armor = false;
			armorBlink = false;
			armorTimeout = 0;
		}
	}
	if(keyBlink)
	{
		keyTimeout -= timePassed;
		if(keyTimeout < 0) // armorTimeout has expired
		{
			keyBlink = false;
			keyTimeout = 0;
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
	jumpCounter = 0;
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
			armorLoss = true;
			armorTimeout = 2.0f;
			soundMgr->playSound(soundArmorLose1);
			jumpCounter = 0;
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
			armorLoss = false;
			armor = true;
			armorTimeout = 2.0f;
			soundMgr->playSound(soundArmorPickup1 + (rand()%2));
			jumpCounter = 0;
		}
	}
}
bool player::getAmorBlink(){return armorBlink;}
void player::flip()
{
	switch(state)
	{
	case walkingRight:
		state = walkingLeft;
		break;
	case walkingLeft:
		state = walkingRight;
		break;
	}
}

void player::setSound(sound * a_soundMgr){soundMgr = a_soundMgr;}

void player::keyPickup()
{
	if(!hasKey)
	{
		if(!keyBlink)
		{
			keyBlink = true;
			hasKey = true;
			keyTimeout = 2.0f;
			// TODO: play key pickup sound
			//soundMgr->playSound(soundArmorPickup1 + (rand()%2));
		}
	}
}
void player::removeKey()
{
	if(hasKey)
	{
		if(!keyBlink)
		{
			keyBlink = true;
			hasKey = false;
			keyTimeout = 2.0f;
			// TODO: play door open sound
			//soundMgr->playSound(soundArmorLose1);
		}
	}
}
bool player::getKeyBlink(){return keyBlink;}
bool player::playerHasKey(){return hasKey;}