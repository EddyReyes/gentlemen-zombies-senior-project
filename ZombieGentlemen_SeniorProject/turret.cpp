#include "turret.h"

turret::turret()
{
	time = 0;
	state = fortyFiveRight;
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

	// the turrets do not move, so they dont really need up go through this extra step
	// m_object->getCollisionRect()->update();
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