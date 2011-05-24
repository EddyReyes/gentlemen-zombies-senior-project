#include "projectile.h"

projectile::projectile()
{
	m_object = NULL;
	state = fire;
	time = 0;
	
}
projectile::~projectile()
{

}

void projectile::update(float timePassed)
{
	time += timePassed;
	if(time <= 1.0f)
	{
		
		firing(timePassed);
		animate();
		time = 0;
	}

}
//face Down function
void projectile::returnTurret()
{
	
}
void projectile::animate()
{
	switch(state)
		{

			case fire:
				
				m_object->setSprite(0, 0);
				m_object->getCollisionRect()->update();
				state = hit;

				break;

			case hit:

				m_object->setSprite(0, 1);
				state = fire;
				break;
		}

}
void projectile::reset()
{
	
}
void projectile::firing(float a_updateTime)
{
	state = fire;
	pos = m_object->getPosition();
	pos->x += 1 * a_updateTime;
	//pos->y += 1 * a_updateTime;
}