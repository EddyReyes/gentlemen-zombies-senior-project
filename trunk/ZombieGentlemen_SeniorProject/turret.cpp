#include "turret.h"

turret::turret()
{
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

	case faceUP:
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
	if(side == 'b'){wallState = faceUP;}
	// if turret is on a left wall then it is facing right
	if(side == 'l'){wallState = faceRight;}
	// if turret is on a right wall then it is facing left
	if(side == 'r'){wallState  = faceLeft;}
}
void setProjectiles(object * proj1, object * proj2, object * proj3, object * proj4, object * proj5)
{

}