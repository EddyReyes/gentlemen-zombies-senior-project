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
	animate();
	

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