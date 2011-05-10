#include "goomba.h"

goomba::goomba()
{
	type = enemyEntity;
	m_object = NULL;
}

goomba::~goomba()
{
	// destruction of the goomba object will happen in the object manager
}

void goomba::update(float timePassed)
{
	// nothing here yet
}