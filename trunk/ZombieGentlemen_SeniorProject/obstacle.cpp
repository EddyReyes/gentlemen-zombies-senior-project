#include "obstacle.h"

/******************
constructor
sets m_object to NULL
******************/
obstacle::obstacle()
{
	m_object = NULL;
}

/******************
constructor
does nothing for now, since the object is part of the object manager,
and destruction of all objects is handle there
******************/
obstacle::~obstacle()
{
	m_object->~object();
}
void obstacle::loadTrap()
{
	m_object->setSprite(0, 0);
	m_object->getCollData();
	m_object->checkCollision();
}
