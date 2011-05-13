#include "turret.h"

turret::turret()
{
	time = 0;
}
turret::~turret()
{

}

void turret::update(float timePassed)
{
	time += timePassed;
	if(time <= 1.0f)
	{
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
	}

	// the turrets do not move, so they dont really need up go through this extra step
	// m_object->getCollisionRect()->update();
}

void turret::animate()
{

}