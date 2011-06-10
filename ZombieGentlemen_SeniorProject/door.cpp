#include "door.h"

door::door(void)
{
	type = stuff_door;
	m_object = NULL;
	state = doorClosed;
}

door::~door(void)
{
	// stuff class does not destroy objects
}

void door::update(float updateTime)
{
	if(state == doorOpen)
	{
		m_object->collisionToggleOff();
		animate();
	}
}
void door::animate()
{
	switch(state)
	{
	case doorOpen: m_object->setSprite(0,1);
		break;
	case doorClosed: m_object->setSprite(0,0);
		break;
	}
}
void door::open(){state = doorOpen;}
bool door::isOpen()
{
	if(state == doorOpen)
		return true;
	else return false;
}