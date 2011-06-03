#include "turret.h"

turret::turret()
{
	type = entityTurret;
	turretTimer = 5;
	state = fortyFiveRight;
	wallState = faceUp;
	bullets = NULL;
	bulletIterator = 0;
}
turret::~turret()
{
	if(bullets)
	{
		destroyProjectiles();
	}
}

void turret::update(float timePassed)
{
	
	turretTimer += timePassed;
	if(turretTimer >= 5.0f)
	{
		animate();
		for(int i = 0; i< numProjectiles; i++)
		{
			bullets[i].setDirection(int(wallState), int(state));
			bullets[i].reset();
		}
		turretTimer = 0;
		bulletIterator = 0;
	}
	else
	{
		if((turretTimer >= 0.5f * bulletIterator) && (bulletIterator < numProjectiles))
		{
			bullets[bulletIterator].fire();
			bulletIterator++;
		}
		for(int i = 0; i< numProjectiles; i++)
		{
			bullets[i].update(timePassed);
		}
	}
}

void turret::animate()
{
	switch(wallState)
	{
	case faceRight:
		switch(state)
			{
			case fortyFiveRight:
				m_object->setSprite(2, 2);
				state = ninety;
				break;

			case ninety:
				m_object->setSprite(2, 1);
				state = fortyFiveLeft;
				break;

			case fortyFiveLeft:
				m_object->setSprite(2, 0);
				state = fortyFiveRight;
				break;
			}
		break;
	case faceDown:
		switch(state)
			{
			case fortyFiveRight:
				m_object->setSprite(0, 0);
				state = ninety;
				break;

			case ninety:
				m_object->setSprite(0, 1);
				state = fortyFiveLeft;
				break;

			case fortyFiveLeft:
				m_object->setSprite(0, 2);
				state = fortyFiveRight;
				break;
			}
		break;

	case faceUp:
		switch(state)
			{
			case fortyFiveRight:
				m_object->setSprite(1, 1);
				state = ninety;
				break;

			case ninety:
				m_object->setSprite(1, 0);
				state = fortyFiveLeft;
				break;

			case fortyFiveLeft:
				m_object->setSprite(1, 2);
				state = fortyFiveRight;
				break;
			}
		break;

	case faceLeft:
		switch(state)
			{
			case fortyFiveRight:
				m_object->setSprite(3, 0);
				state = ninety;
				break;

			case ninety:
				m_object->setSprite(3, 1);
				state = fortyFiveLeft;
				break;

			case fortyFiveLeft:
				m_object->setSprite(3, 2);
				state = fortyFiveRight;
				break;
			}
		break;
	}
}
void turret::reset()
{
	alive = true;
	armor = false;
}
void turret::setWall(char side)
{
	// if turret is on a top wall it is facing down
	if(side == 'd'){wallState = faceDown;}
	// if turret is on a bottom wall then it is facing up
	if(side == 'u'){wallState = faceUp;}
	// if turret is on a left wall then it is facing right
	if(side == 'r'){wallState = faceRight;}
	// if turret is on a right wall then it is facing left
	if(side == 'l'){wallState  = faceLeft;}
}
void turret::setProjectiles(object ** a_projectiles, int a_numProjectiles)
{
	numProjectiles = a_numProjectiles;
	// set objects for projectiles
	bullets = new projectile[numProjectiles];

	for(int i = 0; i < numProjectiles; i++)
	{
		if(a_projectiles[i])
		{
			// toggle collision for projectiles so they can move through each other
			a_projectiles[i]->toggleCollision();
			bullets[i].setObject(a_projectiles[i]);
		}
		else
		{
			MessageBox(NULL, "Error: could not load projectiles", "Turret Error", MB_OK);
		}
	}
}
void turret::hideProjectiles()
{
	float xOffset, yOffset; // this will hide the projectiles behind the turret
	switch(wallState)
	{
	case faceDown: 
		xOffset = 0.5f; // these values could change
		yOffset = -0.4f;
		break;
	case faceUp: 
		xOffset = 0.35f; // these values could change
		yOffset = -0.7f;
		break;
	case faceLeft:
		xOffset = 0.2f; // these values could change
		yOffset = -0.5f;
		break;
	case faceRight:
		xOffset = 0.2f; // these values could change
		yOffset = -0.5f;
		break;
	default: 
		xOffset = 0; // these values could change
		yOffset = 0;
		break;
	}
	for(int i = 0; i < numProjectiles; i++)
	{
		// the projectiles must be hiden behind the turret
		D3DXVECTOR3 * pos = this->getObject()->getPosition();
		bullets[i].setPosition(pos->x + xOffset, pos->y + yOffset);
		bullets[i].init(D3DXVECTOR3(pos->x + xOffset, pos->y + yOffset, 0), 2);
		bullets[i].setDirection(int(wallState), int(state));
	}
}
int turret::getNumProjectiles(){return numProjectiles;}
projectile * turret::getProjectile(int index){return &(bullets[index]);}
void turret::destroyProjectiles()
{
	delete [] bullets;
	bullets = NULL;
}
void turret::flip()
{
	// turrets do not flip
}