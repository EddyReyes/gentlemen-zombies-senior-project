#include "projectile.h"

projectile::projectile()
{
	m_object = NULL;
	state = fire;
}
projectile::~projectile()
{

}

void projectile::update()
{
	D3DXVECTOR3 * pos;
	pos = m_object->getPosition();

	switch(state)
		{

			case fire:

				m_object->setSprite(0, 0);
				//pos->x += 0.5f * timePassed;
				m_object->getCollisionRect()->update();
				break;

			case hit:

				m_object->setSprite(0, 1);
				break;
		}

}