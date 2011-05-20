#include "turret.h"

turret::turret()
{
	type = entityTurret;
	time = 0;
	state = fortyFiveRight;
	bullets = NULL;
}
turret::~turret()
{

}

void turret::update(float timePassed)
{
	time += timePassed;
	if(time <= 1.0f)
	{
		animate();
		time = 0;
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

	case faceLeft:
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
	if(side == 't'){wallState = faceDown;}
	// if turret is on a bottom wall then it is facing up
	if(side == 'b'){wallState = faceUp;}
	// if turret is on a left wall then it is facing right
	if(side == 'l'){wallState = faceRight;}
	// if turret is on a right wall then it is facing left
	if(side == 'r'){wallState  = faceLeft;}
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
	float offset; // this will hide the projectiles behind the turret
	switch(wallState)
	{
	case faceDown: offset = 0.2f; // these values could change
		break;
	case faceUp: offset = 0.2f;
		break;
	case faceLeft: offset = 0.2f;
		break;
	case faceRight: offset = 0.2f;
		break;
	default:  offset = 0.2f;
		break;
	}
	for(int i = 0; i < numProjectiles; i++)
	{
		// the projectiles must be hiden behind the turret
		D3DXVECTOR3 * pos = this->getObject()->getPosition();
		bullets[i].setPosition(pos->x + offset, pos->y + offset);
	}
}
int turret::getNumProjectiles(){return numProjectiles;}
projectile * turret::getProjectile(int index){return &(bullets[index]);}
void turret::destroyProjectiles()
{
	delete [] bullets;
}